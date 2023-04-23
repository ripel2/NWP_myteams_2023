/*
** EPITECH PROJECT, 2023
** mynet/client
** File description:
** mynet client header file
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/queue.h>

#include "data.h"

#define CLIENT_BUFFER_SIZE 32768

// fd: The file descriptor of the client
// addr: The address of the client
// read_fds: The fd_set of file descriptors to read from
// write_fds: The fd_set of file descriptors to write to
// needs_exit: Whether the client needs to exit
// server_closed: Whether the server closed the connection
// buffer: The buffer of the client
// buffer_cur: The current size of the buffer
// uuid: The uuid of the client
// username: The username of the client
typedef struct client_s {
    int fd;
    struct sockaddr_in addr;
    fd_set read_fds;
    fd_set write_fds;
    bool needs_exit;
    bool server_closed;
    char buffer[CLIENT_BUFFER_SIZE + 1];
    size_t buffer_cur;
    char uuid[UUID_LENGTH + 1];
    char username[MAX_NAME_LENGTH + 1];
    char use_team_uuid[UUID_LENGTH + 1];
    char use_channel_uuid[UUID_LENGTH + 1];
    char use_thread_uuid[UUID_LENGTH + 1];
} client_t;

/**
 * @brief Initialize a client structure and connect it to a server
 * @param client The client structure to initialize
 * @param ip The ip of the server
 * @param port The port of the server
 * @return 0 on success, the value of errno on failure
*/
int client_init(client_t *, const char *, int);

/**
 * @brief Destroy a client structure and closes the connection
 * @param client The client structure to destroy
*/
void client_destroy(client_t *);

/**
 * @brief Write a line to the client, with a printf-like syntax
 * @param client The client structure to write to
 * @param format The format string (must be null terminated)
 * @param ... The arguments to the format string
 * @return 0 on success, the value of errno on failure
*/
int client_printf(client_t *, const char *, ...);

/**
 * @brief Read from the client and store the data in the buffer
 * @param client The client structure to read from
 * @return 0 on success, the value of errno on failure
*/
int client_read_in_buffer(client_t *client);

/**
 * @brief Checks if the buffer contains a line break '\n' and if it is,
 * copies it to the line parameter and removes it from the buffer
 * @param client The client structure to read from
 * @param line The line to copy the data to
 * @return true if a line was found, false if no line was found
*/
bool client_flush_line(client_t *client, char *line);

/**
 * @brief Handle an event from the server
 * @param client The client structure to read from
 * @param buffer The buffer that has a line of data
 * @return 0 on success, the value of errno on failure
*/
int client_process_event_buffer(client_t *client, char *buffer);
