# Functionnal tests framework for the my teams

## Introduction

This document describes the functionnal tests framework for the my teams project.
It will explain how to write and run tests for the project.

## How to write tests

### Test directory

All the tests are stored in the `tests/functionnal_test_cases` directory at the root of the project.

### Test file

Each test is a JSON file that needs to end with the `.json` extension.

It contains the following fields:
- `name`: the name of the test
- `description`: a description of the test
- `commands`: the list of commands to execute for the test

### Commands

Each command is a JSON object that contains the following fields:
- `name`: the name of the command
- `args`: the arguments of the command
    - the args var is optional for some commands

#### Available commands

The following commands are available:
- `start_server`: starts the server for the test
- `stop_server`: stops the server for the test
- `destroy_server`: stops the server and destroy all of its output
- `start_client`: starts a client for the test
    - `args`:
        - `name`: the name of the client
- `stop_client`: stops a client for the test
    - `args`:
        - `name`: the name of the client
- `destroy_client`: stops a client and destroy all of its output
    - `args`:
        - `name`: the name of the client
- `client_send_line`: sends a line to a client stdin
    - `args`:
        - `name`: the name of the client
        - `line`: the line to send
- `check_stdout`: checks if the server stdout contains a specific line
    - `args`:
        - `line`: the line to check
- `check_stderr`: checks if the server stderr contains a specific line
    - `args`:
        - `line`: the line to check
- `check_client_stdout`: checks if a client stdout contains a specific line
    - `args`:
        - `name`: the name of the client
        - `line`: the line to check
- `check_client_stderr`: checks if a client stderr contains a specific line
    - `args`:
        - `name`: the name of the client
        - `line`: the line to check
- `match_stdout`: checks if a line in the server stdout matches a regex
    - `args`:
        - `regex`: the regex to match
- `match_stderr`: checks if a line in the server stderr matches a regex
    - `args`:
        - `regex`: the regex to match
- `match_client_stdout`: checks if a line in a client stdout matches a regex
    - `args`:
        - `name`: the name of the client
        - `regex`: the regex to match
- `match_client_stderr`: checks if a line in a client stderr matches a regex
    - `args`:
        - `name`: the name of the client
        - `regex`: the regex to match
- `store_match_stdout`: stores a line in the server stdout that matches a regex
    - `args`:
        - `regex`: the regex to match
        - `name`: the name of the variable to store the match
- `store_match_stderr`: stores a line in the server stderr that matches a regex
    - `args`:
        - `regex`: the regex to match
        - `name`: the name of the variable to store the match
- `store_client_match_stdout`: stores a line in a client stdout that matches a regex
    - `args`:
        - `name`: the name of the client
        - `regex`: the regex to match
        - `name`: the name of the variable to store the match
- `store_client_match_stderr`: stores a line in a client stderr that matches a regex
    - `args`:
        - `name`: the name of the client
        - `regex`: the regex to match
        - `name`: the name of the variable to store the match

### Variables and pattern matching

The framework allows to store the result of a regex match in a variable with the `store_*` commands.
The variable can then be used in the `args` of other commands with the `<<VARIABLE_NAME>>(MATCH_GROUP)` syntax.

For example, if the server stdout contains the line `Hello world!`, the following command will store the `world` string in the `var` variable:
```json
{
    "name": "store_match_stdout",
    "args": ["(Hello )(.*)!", "var"]
}
```

The `var` variable can then be used in the `args` field of other commands:
```json
{
    "name": "check_client_stdout",
    "args": ["client", "Hello <<var>>(2)!"]
}
```

## How to run tests

- `python3 tests/functionnal_tests.py`

If you want verbose output, you can use the `-v` option like so:

- `python3 tests/functionnal_tests.py -v`

which will print out each command executed by the framework, in a similar way to strace.

