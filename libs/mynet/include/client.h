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

#define CLIENT_LINE_TERMINATOR "\n"
#define CLIENT_BUFFER_SIZE 1024
#define CLIENT_LINE_TERMINATOR_SIZE 1

// line: The line of the client
// length: The length of the line
// entries: The entries of the line (for the TAILQ list)
typedef struct line_s {
    char *buf;
    size_t len;
    TAILQ_ENTRY(line_s) entries;
} line_t;


// fd: The file descriptor of the client
// addr: The address of the client
// read_fds: The fd_set of file descriptors to read from
// write_fds: The fd_set of file descriptors to write to
// buffer: The buffer of the client
// lines: The lines of the client
typedef struct client_s {
    int fd;
    struct sockaddr_in addr;
    fd_set read_fds;
    fd_set write_fds;
    bool needs_exit;
    char buffer[CLIENT_BUFFER_SIZE];
    TAILQ_HEAD(line_list_s, line_s) lines;
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
 * @brief Destroy a client structure, closes the connection and frees the
 * memory used by the structure (for lines)
 * @param client The client structure to destroy
*/
void client_destroy(client_t *);

/**
 * @brief Write data to the client
 * @param client The client structure to write to
 * @param buffer The buffer to write from
 * @param buffer_size The size of the buffer
 * @return 0 on success, the value of errno on failure
*/
int client_write(client_t *, const char *, size_t);

/**
 * @brief Write a null-terminated string to the client
 * @param client The client structure to write to
 * @param buffer The buffer to write from
 * @return 0 on success, the value of errno on failure
*/
int client_write_string(client_t *, const char *);

/**
 * @brief Write a line to the client, with a printf-like syntax
 * @param client The client structure to write to
 * @param format The format string (must be null terminated)
 * @param ... The arguments to the format string
 * @return 0 on success, the value of errno on failure
*/
int client_printf(client_t *, const char *, ...);

/**
 * @brief Read lines from a client. This function will call select and read
 * from the client's file descriptor while there is data to read. The lines
 * will be stored in the client's line list.
 * @param client The client to read from
 * @return 0 on success, the value of errno on failure
*/
int client_read_lines(client_t *);

/**
 * @brief Gets the first line of the client and removes it from the list.
 * The line must be freed after use.
 * @param client The client structure to read from
 * @return The first line of the client, or NULL if the client has no lines
*/
line_t *client_pop_line(client_t *);

/**
 * @brief Gets the first line of the client.
 * @param client The client structure to read from
 * @return The first line of the client, or NULL if the client has no lines
*/
line_t *client_peek_line(client_t *);
