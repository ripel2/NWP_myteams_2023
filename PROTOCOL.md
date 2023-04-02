# MyTeams communication protocol

## 1. Introduction

This document describes the communication protocol between the MyTeams client and the MyTeams server.

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


