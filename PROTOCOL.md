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
<br>`COMMAND "arg 1" "arg 2"\n` Command with two arguments that has spaces in them
<br>`COMMAND  \n` Command with an empty argument
<br>`COMMAND arg1  \n` Command with an argument and an empty argument
<br>
In the client specification, the arguments should always be surrounded by double quotes (`"`), but it is not mandatory in the server. Of course, when the data has spaces in it, there should be double quotes.

## 3. Data transfer

In this section, we describe the data transfer between the client and the server.

### 3.1. Response format

A response is a string of characters that ends with a newline character (`\n`). The response always starts with a three-digit number.
Arguments after the reply code can be surrounded by double quotes (`"`) if necessary.

### 3.2. Response codes

The first digit of the response code indicates the type of response:
- `1xx` Informational response: the request was received and the process is continuing
- `2xx` Successful response: the action was successfully received, understood, and accepted
- `3xx` Redirection response: further action must be taken in order to complete the request
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
| 451 | Error | Already exists | When the user tries to create a ressource that already exists |
| 500 | Server error | Syntax error, command unrecognized | When the user sends a command that doesn't exist |
| 501 | Server error | Syntax error in parameters or arguments | When the user sends a command with invalid arguments |
| 502 | Server error | Command not implemented | When the user sends a command that is specified in the protocol but not implemented |
| 530 | Server error | Not logged in | When the user tries to perform an action that requires them to be logged in |
| 550 | Server error | Requested action not taken | When the user tries to do something not possible (e.g message too long or title too long) Also used for internal server errors |

### 3.4. Service commands

The service commands are used to control the connection between the client and the server.
Here is the list of all the service commands available:

| Command | Arguments | Description | Example | Responses |
| --- | --- | --- | --- | --- |
| HELP | None | Get the list of all the commands | `HELP\n` | 214 ... |
| LOGIN | username | Log in to the server | `LOGIN <username>\n` | 230 `<uuid>` Logged in<br>431 Already logged in<br>550 Username too long |
| LOGOUT | None | Log out from the server | `LOGOUT\n` | 221 `<uuid>` Logged out<br>530 Not logged in |
| USERS | None | Get the list of all the users | `USERS\n` | 150 ...<br>530 Not logged in |
| USER | user_uuid | Get details about a given user | `USER <uuid>\n` | 150 ...<br>430 User doesn't exist<br>530 Not logged in<br>550 Bad uuid|
| SEND | user_uuid message | Send a message to a user | `SEND <uuid> <message>\n` | 200 OK<br>430 User doesn't exist<br>530 Not logged in |
| MESSAGES | user_uuid | Get all messages exchanged with the given user | `MESSAGES <uuid>\n` | 150 ...<br>430 User doesn't exist<br>530 Not logged in<br>550 Bad uuid |
| SUBSCRIBE | team_uuid | Subscribe to a team | `SUBSCRIBE <uuid>\n` | 200 OK<br>430 Team doesn't exist<br>530 Not logged in<br>550 Bad uuid |
| SUBSCRIBED | None | Get the list of all the teams the user is subscribed to | `SUBSCRIBED\n` | 150 ...<br>530 Not logged in |
| SUBSCRIBED | team_uuid | Get the list of all the users subscribed to a given team | `SUBSCRIBED <uuid>\n` | 150 ...<br>430 Team doesn't exist<br>530 Not logged in<br>550 Bad uuid |
| UNSUBSCRIBE | team_uuid | Unsubscribe from a team | `UNSUBSCRIBE <uuid>\n` | 200 OK<br>430 Team doesn't exist<br>530 Not logged in<br>550 Bad uuid |
| The following commands will be interpreted in the context set by the previous commands |
| USE (TEAM) | team_uuid | Sets the command context to the given team | `USE <uuid>\n` | 110 OK<br>430 Team doesn't exist<br>530 Not logged in<br>550 Bad uuid |
| USE (CHANNEL) | channel_uuid | Sets the command context to the given channel | `USE <uuid>\n` | 110 OK<br>430 Channel doesn't exist or doesn't belong to team<br>530 Not logged in<br>550 Bad uuid |
| USE (THREAD) | thread_uuid | Sets the command context to the given thread | `USE <uuid>\n` | 110 OK<br>430 Thread doesn't exist or doesn't belong to channel<br>530 Not logged in<br>550 Bad uuid |
| CREATE (TEAM) | team_name description | Create a new team | `CREATE <name> <description>\n` | 150 `<uuid>`<br>530 Not logged in<br>550 Name or description too long |
| CREATE (CHANNEL) | channel_name channel_description | Create a new channel | `CREATE <name> <description>\n` | 150 `<uuid>`<br>530 Not logged in<br>550 Name or description too long<br>451 Already exists |
| CREATE (THREAD) | thread_title thread | Create a new thread | `CREATE <title> <message>\n` | 150 `<uuid>`<br>530 Not logged in<br>550 Title or message too long<br>451 Already exists |
| CREATE (COMMENT) | comment_body | Create a new comment | `CREATE <body>\n` | 150 `<uuid>`<br>530 Not logged in<br>550 Body too long<br>451 Already exists |
| LIST | None | Get the list of all the teams, channels and threads, depending on the context | `LIST\n` | 150 ...<br>530 Not logged in |
| INFO | None | Get details about the user, the team, channel and thread, depending on the context | `INFO\n` | 150 ...<br>530 Not logged in |

### 3.5. Service command answers

This is the list of all the possible answers for the service commands.
They are only described if the answer is different from the one described in the table above.

#### 3.5.1. `HELP`

The `HELP` command is used to get the list of all the commands available.
The client should send the `HELP` command followed by a newline character (`\n`).
The server will then send a list of all the commands available, each command separated by a space.

Example of a `HELP` command:
```
IN  >>> HELP
OUT <<< 214 HELP LOGIN LOGOUT USERS USER SEND MESSAGES SUBSCRIBE SUBSCRIBED UNSUBSCRIBE USETEAM USECHANNEL USETHREAD CREATE LIST INFO
```

#### 3.5.2. `USERS`

The `USERS` command is used to get the list of all the users registered on the server.
The client should send the `USERS` command followed by a newline character (`\n`).
The server will send the number of user first, then all the users separated by newlines.
The message will end with a `200 OK` response.

A user will be represented by the following format:
```
<uuid> <username> <is_logged_in>
```

Example of a `USERS` command:
```
IN  >>> USERS
OUT <<< 150 3
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user1 1
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user2 0
OUT <<< 3e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user3 1
OUT <<< 200 OK
```

### 3.5.3. `USER`

The `USER` command is used to get details about a given user.
The client should send the `USER` command followed by the user uuid and a newline character (`\n`).
The server will send the user details if the user exists, otherwise it will send a `430 User doesn't exist` response.

A user will be represented by the following format:
```
<uuid> <username> <is_logged_in>
```

Example of a `USER` command:
```
IN  >>> USER 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user1 1
```
If the user is not logged in:
```
IN  >>> USER 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user1 0
```

### 3.5.4. `SEND`

The `SEND` command is used to send a message to a given user.
The client should send the `SEND` command followed by the user uuid, the message and a newline character (`\n`).
The client should then send the message and a newline character (`\n`).

Example of a `SEND` command:
```
IN  >>> SEND 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f message
OUT <<< 200 OK
```

### 3.5.5. `MESSAGES`

The `MESSAGES` command is used to get all the messages exchanged with a given user.
The client should send the `MESSAGES` command followed by the user uuid and a newline character (`\n`).
The server will send the number of messages first, then all the messages separated by newlines.
The message will end with a `200 OK` response.

A message will be represented by the following format:
```
<FROM/TO> <timestamp> <message>
```

Example of a `MESSAGES` command:
```
IN  >>> MESSAGES 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
OUT <<< 150 2
OUT <<< FROM 12345678 message
OUT <<< TO 12345678 message
OUT <<< 200 OK
```
(first number is the timestamp of the message)

### 3.5.6. `SUBSCRIBED`

The `SUBSCRIBED` command can be used either to get the list of all the teams the user is subscribed to, or to get the list of all the users subscribed to a given team.
The client should send the `SUBSCRIBED` command followed by the team uuid and a newline character (`\n`).
The server will send the number of teams/users first, then all the teams/users separated by newlines.
The message will end with a `200 OK` response.

A team will be represented by the following format:
```
<uuid> <name> <description>
```

A user will be represented by the following format:
```
<uuid> <username>
```

Example of a `SUBSCRIBED` command without arguments (get the list of all the teams the user is subscribed to):
```
IN  >>> SUBSCRIBED
OUT <<< 150 2
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team1 description
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team2 description
OUT <<< 200 OK
```

Example of a `SUBSCRIBED` command with a team uuid (get the list of all the users subscribed to a given team):
```
IN  >>> SUBSCRIBED 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
OUT <<< 150 2
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user1
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user2
```

### 3.5.7. `LIST`

The `LIST` command can be used in multiple contexts:
 - If the client didn't register any context, the server will send the list of all the teams.
 - If the client registered a team context, the server will send the list of all the channels in the team.
 - If the client registered a team and a channel context, the server will send the list of all the threads in the channel.
 - If the client registered a team, a channel and a thread context, the server will send the list of all the existing replies in the thread.

The client should send the `LIST` command followed by a newline character (`\n`).
The server will send the number of teams/channels/threads/replies first, then all the teams/channels/threads/replies separated by newlines.
The message will end with a `200 OK` response.

Example of a `LIST` command without any context:
```
IN  >>> LIST
OUT <<< 150 2 TEAMS
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team1 description
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team2 description
OUT <<< 200 OK
```

Example of a `LIST` command with a team context:
```
IN  >>> LIST
OUT <<< 150 2 CHANNELS
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f channel1 channel_description
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f channel2 channel_description
OUT <<< 200 OK
```

Example of a `LIST` command with a team and a channel context:
```
IN  >>> LIST
OUT <<< 150 2 THREADS
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 thread1 thread_description
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 thread2 thread_description
OUT <<< 200 OK
```
(the first number is the timestamp of the thread creation)

Example of a `LIST` command with a team, a channel and a thread context:
```
IN  >>> LIST
OUT <<< 150 2 REPLIES
OUT <<< 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 reply1 message
OUT <<< 2e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 reply2 message
OUT <<< 200 OK
```
(the first number is the timestamp of the reply creation)

### 3.5.8. `INFO`

The `INFO` command can be used in multiple contexts:
 - If the client didn't register any context, the server will send the information about a given team.
 - If the client registered a team context, the server will send the information about a given channel in the team.
 - If the client registered a team and a channel context, the server will send the information about a given thread in the channel.
 - If the client registered a team, a channel and a thread context, the server will send the information about a given reply in the thread.

The client should send the `INFO` command followed by a newline character (`\n`).
The server will send the information and the description/username.

Example of a `INFO` command without any context (print user details)
```
IN  >>> INFO
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f user1
```

Example of a `INFO` command with a team context:
```
IN  >>> INFO
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f description
```

Example of a `INFO` command with a team and a channel context:
```
IN  >>> INFO
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f description
```

Example of a `INFO` command with a team, a channel and a thread context:
```
IN  >>> INFO
OUT <<< 150 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 description
```
(first number is the timestamp of the thread creation)

### 3.5.9. `CREATE`

The `CREATE` command can be used in multiple contexts:
 - If the client didn't register any context, the server will create a new team.
 - If the client registered a team context, the server will create a new channel in the team.
 - If the client registered a team and a channel context, the server will create a new thread in the channel.
 - If the client registered a team, a channel and a thread context, the server will create a new reply in the thread.

The client should send the `CREATE` command followed by the uuid of the team/channel/thread/reply and and the description of the team/channel/thread/reply.

Example of a `CREATE` command without any context:
```
IN  >>> CREATE 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f description
OUT <<< 200 <created_uuid>
```

Example of a `CREATE` command with a team context:
```
IN  >>> CREATE 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f description
OUT <<< 200 <created_uuid>
```

Example of a `CREATE` command with a team and a channel context:
```
IN  >>> CREATE 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f description
OUT <<< 200 <created_uuid>
```

Example of a `CREATE` command with a team, a channel and a thread context:
```
IN  >>> CREATE 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f message
OUT <<< 200 <created_uuid>
```

# 4. Client events

The client can receive events from the server at any time. The client should be able to handle the following events:
 - client_event_logged_in
 - client_event_logged_out
 - client_event_private_message_received
 - client_event_team_created
 - client_event_channel_created
 - client_event_thread_created
 - client_event_thread_reply_received

## 4.1. `client_event_logged_in`

The `client_event_logged_in` event is sent by the server to every user logged in when a new user logs in.

The server will send the `client_event_logged_in` event followed by the uuid of the user who logged in.

Example of a `client_event_logged_in` event:
```
IN <<< client_event_logged_in 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
```

## 4.2. `client_event_logged_out`

The `client_event_logged_out` event is sent by the server to every user logged in when a user logs out.

The server will send the `client_event_logged_out` event followed by the uuid of the user who logged out.

Example of a `client_event_logged_out` event:
```
IN <<< client_event_logged_out 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f
```

## 4.3. `client_event_private_message_received`

The `client_event_private_message_received` event is sent by the server to the user when a private message is received.
Of course, it is only sent if the user is logged in.

The server will send the `client_event_private_message_received` event followed by the uuid of the user who sent the message
and the message itself.

Example of a `client_event_private_message_received` event:
```
IN <<< client_event_private_message_received 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f message
```

## 4.4. `client_event_team_created`

The `client_event_team_created` event is sent by the server to every user logged in when a new team is created.

The server will send the `client_event_team_created` event followed by the uuid of the team, the name of the team
and the description of the team.

Example of a `client_event_team_created` event:
```
IN <<< client_event_team_created 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team1 description
```

## 4.5. `client_event_channel_created`

The `client_event_channel_created` event is sent by the server when a new channel is created in a team.
It is sent to every user that belongs to the team and is logged in.

The server will send the `client_event_channel_created` event followed by the uuid of the channel, the name of the channel
and the description of the channel.

Example of a `client_event_channel_created` event:
```
IN <<< client_event_channel_created 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f channel1 description
```

## 4.6. `client_event_thread_created`

The `client_event_thread_created` event is sent by the server when a new thread is created in a channel.
It is sent to every user that belongs to the channel and is logged in.

The server will send the `client_event_thread_created` event followed by the uuid of the thread, the uuid of the
user that created the thread, the timestamp of creation, the title of the thread and the message of the thread.

Example of a `client_event_thread_created` event:
```
IN <<< client_event_thread_created 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1234567 title message
```

## 4.7. `client_event_thread_reply_received`

The `client_event_thread_reply_received` event is sent by the server when a new reply is created in a thread.
It is sent to every user that belongs to the thread and is logged in.

The server will send the `client_event_thread_reply_received` event followed by the uuid of the team, the uuid of the thread,
the uuid of the user that created the reply and the body of the reply.

Example of a `client_event_thread_reply_received` event:
```
IN <<< client_event_thread_reply_received 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f 1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f message
```
