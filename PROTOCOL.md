# MyTeams communication protocol

## 1. Introduction

This document describes the communication protocol between the MyTeams client and the MyTeams server.
It is heavily inspired by the [FTP protocol](https://tools.ietf.org/html/rfc959).

## 2. General rules

In this section, we describe the general rules that must be followed by the client and the server.

### 2.1. Inner communication

The client and the server communicate using a command-based protocol. The client sends a command to the server, and the server replies with a response. The client can send a command at any time, and the server can reply at any time.

### 2.2. Command format

A command is a string of characters that ends with a newline character (`\n`). The command is composed of a command name, and a list of arguments separated by spaces.
<br>
The command name is a string of characters that does not contain spaces and is in capital letters.
<br>
The arguments are a list of strings of characters that can contain spaces. The arguments are separated by spaces.
<br>
The arguments can be empty strings. In this case, the command can have two spaces in a row.
<br>
Examples of valid commands:
<br>`COMMAND\n` Command with no arguments
<br>`COMMAND arg1\n` Command with one argument
<br>`COMMAND arg1 arg2\n` Command with two arguments
<br>`COMMAND  \n` Command with an empty argument
<br>`COMMAND arg1  \n` Command with an argument and an empty argument

## 3. Data transfer

### 3.1. Response format

A response is a string of characters that ends with a newline character (`\n`). The response always starts with a three-digit number.

### 3.2. Response codes

The first digit of the response code indicates the type of response:
- `1xx` Informational response: the request was received and the process is continuing
- `2xx` Successful response: the action was successfully received, understood, and accepted
- `3xx` Redirection response: further action must be taken in order to complete the request
    - Won't be used in this project
- `4xx` Client error response: the request contains bad syntax or cannot be fulfilled
- `5xx` Server error response: the server failed to fulfill an apparently valid request

The second digit of the response code indicates the category of response:
- `x0x` Syntax: the command was not correctly formatted
- `x1x` Information: used for responses that are informational only
- `x2x` Connections: responses related to the control and data connections
- `x3x` Authentication and accounting: responses related to authentication and accounting
- `x4x` Unspecified: responses that do not fit in any other category
- `x5x` Database: responses related to the Teams database (get messages, list users, etc.)

The third digit of the response code is specific to the response.

### 3.3. All reply codes

Responses messages are not standardized. Thus, the client should rely on the response code to determine the type of response.
Here is a list of all the response codes that can be sent by the server:

| Code | Category | Description | Example |
| --- | --- | --- | --- |
| 110 | Information | Intermediate response | When the client uses a command that should update its state |
| 150 | Information | Intermediate response | When the client uses a command that should send back some data |
| 200 | Success | Command OK | When the user sends a message |
| 214 | Success | Help message | When the user sends the "help" command |
| 220 | Success | Service ready for new user | When the user connects to the server |
| 221 | Success | Service closing control connection | When the user disconnects from the server using the "logout" command |
| 230 | Success | User logged in, proceed | When the user logs in using the "login" command |
| 430 | Error | Ressource doesn't exist | When the user tries to interact with a ressource (team, channel, user, etc.) that doesn't exist |
| 431 | Error | Cannot perform action | When the user tries to perform an action that they are not allowed to do |
| 500 | Server error | Syntax error, command unrecognized | When the user sends a command that doesn't exist |
| 501 | Server error | Syntax error in parameters or arguments | When the user sends a command with invalid arguments |
| 502 | Server error | Command not implemented | When the user sends a command that is specified in the protocol but not implemented |
| 530 | Server error | Not logged in | When the user tries to perform an action that requires them to be logged in |
| 550 | Server error | Requested action not taken | When the user tries to do something not possible (e.g message too long or title too long) |

