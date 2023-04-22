import subprocess
import threading
import json
import os
import re
import time
import select
import colorama
import fcntl
import sys
import queue

colorama.init()

OK_COLOR = colorama.Fore.GREEN + colorama.Style.BRIGHT
KO_COLOR = colorama.Fore.RED + colorama.Style.BRIGHT
RESET_COLOR = colorama.Style.RESET_ALL

from typing import SupportsInt, List, Tuple, Dict, AnyStr

MYTEAMS_CLI = "./myteams_cli"
MYTEAMS_SERVER = "./myteams_server"


class CommandRunner:
    """Class to run shell commands in a separate thread and get their output"""

    def __init__(self, command):
        self.command = command
        self.process = None
        self._stdout = bytearray()
        self._stderr = bytearray()
        self._stdout_lock = threading.Lock()
        self._stderr_lock = threading.Lock()
        self.__kill_event = threading.Event()
        self._thread = threading.Thread(target=self._run)
        self._thread.start()

    def _run(self):
        self.process = subprocess.Popen(
            self.command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            stdin=subprocess.PIPE
        )
        fcntl.fcntl(self.process.stdout.fileno(), fcntl.F_SETFL, os.O_NONBLOCK)
        fcntl.fcntl(self.process.stderr.fileno(), fcntl.F_SETFL, os.O_NONBLOCK)

        while self.process.poll() is None:
            if self.__kill_event.is_set():
                break
            with self._stdout_lock:
                with self._stderr_lock:
                    r, w, e = select.select([self.process.stdout, self.process.stderr], [], [], 0.1)
                    if self.process.stdout in r:
                        data = self.process.stdout.read()
                        if data:
                            self._stdout.extend(data)
                    if self.process.stderr in r:
                        data = self.process.stderr.read()
                        if data:
                            self._stderr.extend(data)

        if self.process.poll() is None and self.__kill_event.is_set():
            self.process.kill()

        with self._stdout_lock:
            data = self.process.stdout.read()
            if data:
                self._stdout += data

        with self._stderr_lock:
            data = self.process.stderr.read()
            if data:
                self._stderr += data

    def get_stderr(self) -> list:
        with self._stderr_lock:
            lines = self._stderr.decode("utf-8").splitlines()
            for line in lines:
                if "error while loading shared libraries: libmyteams.so" in line:
                    print(colorama.Fore.RED + colorama.Style.BRIGHT)
                    print("==================================")
                    print()
                    print("il faut charger la jérélib avant de lancer les tests")
                    print("voici la commande pour le faire :")
                    print("export LD_LIBRARY_PATH=./libs/myteams:$LD_LIBRARY_PATH")
                    print()
                    print("==================================")
                    print(colorama.Style.RESET_ALL)

            return lines

    def send_stdin(self, stdin: str):
        if not self.process:
            return
        if not self.process.stdin:
            return
        if not self.process.poll() is None:
            return
        try:
            self.process.stdin.write(stdin.encode())
            self.process.stdin.flush()
        except:
            pass

    def close_stdin(self):
        if not self.process:
            return
        if not self.process.stdin:
            return
        if not self.process.poll() is None:
            return
        try:
            self.process.stdin.close()
        except:
            pass

    def kill(self):
        self.__kill_event.set()
        try:
            self.process.kill()
        except:
            pass

    def join(self, timeout=None):
        self._thread.join(timeout)

class TestCase:
    VALID_COMMANDS = {
        "start_server": None,
        "stop_server": None,
        "destroy_server": None,
        "start_client": [str],
        "stop_client": [str],
        "destroy_client": [str],
        "client_send_line": [str, str],
        "check_stdout": [str],
        "check_stderr": [str],
        "check_client_stdout": [str, str],
        "check_client_stderr": [str, str],
        "match_stdout": [str],
        "match_stderr": [str],
        "match_client_stdout": [str, str],
        "match_client_stderr": [str, str],
        "store_match_stdout": [str, str],
        "store_match_stderr": [str, str],
        "store_client_match_stdout": [str, str, str],
        "store_client_match_stderr": [str, str, str],
    }

    class TestFailed(Exception):
        pass

    def __init__(self, test_file):
        self._test_file = test_file
        with open(test_file) as f:
            self._test = json.load(f)
        self.name = self._test["name"]
        self.description = self._test["description"]
        self.commands = self._test["commands"]
        for index, command in enumerate(self.commands, 1):
            if not self._command_is_valid(command):
                raise Exception(
                    'Invalid command (command n.{}, "{}") in test file'.format(
                        index, command["name"] if "name" in command else "<UNNAMED>"
                    )
                )
        self.__server = None
        self.__clients = {}
        self.__matches = {}

    def _command_is_valid(self, command: dict) -> bool:
        if "name" not in command:
            return False

        if command["name"] not in self.VALID_COMMANDS:
            return False
        if self.VALID_COMMANDS[command["name"]] is None:
            return True
        if "args" not in command:
            return False
        for index, arg_type in enumerate(self.VALID_COMMANDS[command["name"]]):
            try:
                arg = command["args"][index]
                arg_type(arg)
            except:
                return False
        return True

    def _start_server(self):
        if self.__server is not None:
            raise Exception("Server already started")
        self.__server = CommandRunner([MYTEAMS_SERVER, "4242"])

    def _stop_server(self):
        if self.__server is None:
            raise Exception("Server not started")
        self.__server.kill()

    def _destroy_server(self):
        if self.__server is None:
            raise Exception("Server not started")
        self.__server.kill()
        self.__server = None

    def _start_client(self, client_name: str):
        if client_name in self.__clients:
            raise Exception("Client {} already exists".format(client_name))
        self.__clients[client_name] = CommandRunner(
            [MYTEAMS_CLI, "0.0.0.0", "4242"]
        )

    def _stop_client(self, client_name: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        self.__clients[client_name].close_stdin()
        self.__clients[client_name].join(1)
        self.__clients[client_name].kill()

    def _destroy_client(self, client_name: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        self.__clients[client_name].kill()
        del self.__clients[client_name]

    def _client_send_line(self, client_name: str, stdin: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        if stdin[-1] != '\n':
            stdin += '\n'
        self.__clients[client_name].send_stdin(stdin)

    def _check_stdout(self, expected_line: str):
        if self.__server is None:
            raise Exception("Server not started")
        stdout = self.__server.get_stdout()
        if expected_line[-1] != '\n':
            expected_line += '\n'
        if expected_line not in stdout:
            raise Exception(
                "Expected line not found in server stdout: {}".format(expected_line.strip())
            )

    def _check_stderr(self, expected_line: str):
        if self.__server is None:
            raise Exception("Server not started")
        stderr = self.__server.get_stderr()
        if expected_line[-1] != '\n':
            expected_line += '\n'
        if expected_line not in stderr:
            raise self.TestFailed(
                "Expected line not found in server stderr: {}".format(expected_line.strip())
            )

    def _check_client_stdout(self, client_name: str, expected_line: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        stdout = self.__clients[client_name].get_stdout()
        if expected_line[-1] != '\n':
            expected_line += '\n'
        if expected_line not in stdout and expected_line.strip() not in stdout:
            raise self.TestFailed(
                "Expected line not found in client {} stdout: {}".format(
                    client_name, expected_line.strip()
                )
            )

    def _check_client_stderr(self, client_name: str, expected_line: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        if expected_line[-1] != '\n':
            expected_line += '\n'
        stderr = self.__clients[client_name].get_stderr()
        if expected_line not in stderr and expected_line.strip() not in stderr:
            raise self.TestFailed(
                "Expected line not found in client {} stderr: {}".format(
                    client_name, expected_line.strip()
                )
            )

    def _match_stdout(self, regex: str):
        if self.__server is None:
            raise Exception("Server not started")
        stdout = self.__server.get_stdout()
        for line in stdout:
            if re.match(regex, line):
                return
        raise self.TestFailed(
            "Regex didn't match in server stdout: {}".format(regex)
        )

    def _match_stderr(self, regex: str):
        if self.__server is None:
            raise Exception("Server not started")
        stderr = self.__server.get_stderr()
        for line in stderr:
            if re.match(regex, line):
                return
        raise self.TestFailed(
            "Regex didn't match in server stderr: {}".format(regex)
        )

    def _match_client_stdout(self, client_name: str, regex: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        stdout = self.__clients[client_name].get_stdout()
        for line in stdout:
            if re.match(regex, line):
                return
        raise self.TestFailed(
            "Regex didn't match in client {} stdout: {}".format(
                client_name, regex
            )
        )

    def _match_client_stderr(self, client_name: str, regex: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        stderr = self.__clients[client_name].get_stderr()
        for line in stderr:
            if re.match(regex, line):
                return
        raise self.TestFailed(
            "Regex didn't match in client {} stderr: {}".format(
                client_name, regex
            )
        )

    def _store_match_stdout(self, regex: str, match_name: str):
        if self.__server is None:
            raise Exception("Server not started")
        stdout = self.__server.get_stdout()
        for line in stdout:
            if re.match(regex, line):
                self.__matches[match_name] = re.match(regex, line)
                return
        raise self.TestFailed(
            "Regex didn't match in server stdout: {}".format(regex)
        )

    def _store_match_stderr(self, regex: str, match_name: str):
        if self.__server is None:
            raise Exception("Server not started")
        stderr = self.__server.get_stderr()
        for line in stderr:
            if re.match(regex, line):
                self.__matches[match_name] = re.match(regex, line)
                return
        raise self.TestFailed(
            "Regex didn't match in server stderr: {}".format(regex)
        )

    def _store_client_match_stdout(self, client_name: str, regex: str, match_name: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        stdout = self.__clients[client_name].get_stdout()
        for line in stdout:
            if re.match(regex, line):
                self.__matches[match_name] = re.match(regex, line)
                return
        raise self.TestFailed(
            "Regex didn't match in client {} stdout: {}".format(
                client_name, regex
            )
        )

    def _store_client_match_stderr(self, client_name: str, regex: str, match_name: str):
        if client_name not in self.__clients:
            raise Exception("Client {} does not exist".format(client_name))
        stderr = self.__clients[client_name].get_stderr()
        for line in stderr:
            if re.match(regex, line):
                self.__matches[match_name] = re.match(regex, line)
                return
        raise self.TestFailed(
            "Regex didn't match in client {} stderr: {}".format(
                client_name, regex
            )
        )

    def _apply_matches(self, src: str) -> str:
        regex = r"<<([a-zA-Z_]+)>>\((\d+)\)"
        matches = re.finditer(regex, src)
        for match_to in matches:
            match_name = match_to.group(1)
            match_group = match_to.group(2)
            if match_name not in self.__matches:
                raise Exception("Pattern matching in command \"{}\"\n no variable {}".format(src, match_name))
            match_from = self.__matches[match_name]
            src = src.replace(match_to.group(0), match_from.group(int(match_group)))
        return src

    def destroy(self):
        if self.__server is not None:
            self.__server.kill()
        for client in self.__clients.values():
            client.kill()

    def run(self, timeout=10, verbose=False):
        self.__exceptions = queue.Queue()
        self.__thread_needs_to_die = threading.Event()
        def inner(self):
            for command in self.commands:
                if self.__thread_needs_to_die.is_set():
                    return
                try:
                    command_args = []
                    if self.VALID_COMMANDS[command["name"]] is not None:
                        for arg_type in self.VALID_COMMANDS[command["name"]]:
                            arg = command["args"].pop(0)
                            arg = self._apply_matches(arg)
                            command_args.append(arg_type(arg))
                    if self.__thread_needs_to_die.is_set():
                        return
                    time.sleep(0.1069) # 1/10th of a second with some crunchy bits
                    if self.__thread_needs_to_die.is_set():
                        return
                    if verbose:
                        print(command["name"] + "({})".format(", ".join(map(str, command_args))), end=" = ")
                    try:
                        getattr(self, "_{}".format(command["name"]))(*command_args)
                        if verbose:
                            print(OK_COLOR + "OK" + RESET_COLOR)
                    except Exception as e:
                        if verbose:
                            print(KO_COLOR + "KO" + RESET_COLOR)
                        raise e
                    if self.__thread_needs_to_die.is_set():
                        return
                except Exception as e:
                    self.__exceptions.put(e)
                    return

        thread = threading.Thread(target=inner, args=(self,))
        thread.start()
        thread.join(timeout)
        self.destroy()

        if thread.is_alive():
            self.__thread_needs_to_die.set()
            raise Exception("Timed out")
        try:
            exception = self.__exceptions.get(False, None)
        except queue.Empty:
            exception = None
        if exception:
            raise exception


if __name__ == "__main__":
    verbose = "-v" in sys.argv

    passed, failed, crashed = 0, 0, 0

    for file in os.listdir("./tests/functionnal_test_cases"):
        if file.endswith(".json"):
            print("=" * 80)
            print("Loading test file {}...".format(file), end=" ")
            try:
                test = TestCase("./tests/functionnal_test_cases/" + file)
            except Exception as e:
                print(KO_COLOR + "\nError while parsing test file: {}".format(e) + RESET_COLOR)
                print()
                print("=" * 80)
                crashed += 1
                continue

            print(OK_COLOR + "OK" + RESET_COLOR)
            print()
            print("NAME\t\t{}".format(test.name))
            print("DESCRPITION\t{}".format(test.description))
            print()
            try:
                print("Running test...")
                test.run(verbose=verbose)
                print(OK_COLOR + "Test passed" + RESET_COLOR)
                passed += 1
            except test.TestFailed as e:
                print(KO_COLOR + "Test failed")
                print(str(e) + RESET_COLOR)
                failed += 1
            except Exception as e:
                print(KO_COLOR + "Test crashed")
                print(str(e) + RESET_COLOR)
                crashed += 1
            print("=" * 80)
            print()

    print("Passed: {}".format(passed))
    print("Failed: {}".format(failed))
    print("Crashed: {}".format(crashed))
    if failed > 0 or crashed > 0:
        print(KO_COLOR + "There is some crunchy bits in the project..." + RESET_COLOR)
        os._exit(1)
    else:
        print(OK_COLOR + "The project is not crunchy" + RESET_COLOR)
