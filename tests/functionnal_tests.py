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

        with self._stdout_lock:
            with self._stderr_lock:
                self._stdout += self.process.stdout.read()
                self._stderr += self.process.stderr.read()

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
        if expected_line not in stdout:
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
        if expected_line not in stderr:
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

    def destroy(self):
        if self.__server is not None:
            self.__server.kill()
        for client in self.__clients.values():
            client.kill()

    def run(self, timeout=10, verbose=False):
        self.__exceptions = queue.Queue()
        def inner(self):
            for command in self.commands:
                try:
                    command_args = []
                    if self.VALID_COMMANDS[command["name"]] is not None:
                        for arg_type in self.VALID_COMMANDS[command["name"]]:
                            command_args.append(arg_type(command["args"].pop(0)))
                    time.sleep(0.1069) # 1/10th of a second with some crunchy bits
                    if verbose:
                        print(command["name"] + "({})".format(", ".join(map(str, command_args))))
                    getattr(self, "_{}".format(command["name"]))(*command_args)
                except Exception as e:
                    self.__exceptions.put(e)
                    break

        thread = threading.Thread(target=inner, args=(self,))
        thread.start()
        thread.join(timeout)
        if thread.is_alive():
            raise Exception("Timed out")
        if not self.__exceptions.empty():
            raise self.__exceptions.get()

        self.destroy()


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
        exit(1)
    else:
        print(OK_COLOR + "The project is not crunchy" + RESET_COLOR)
