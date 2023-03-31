/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server header file
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/queue.h>

#define SERVER_LISTEN_BACKLOG 10
#define SERVER_CLIENT_BUFFER_SIZE 6
#define SERVER_LINE_TERMINATOR "\n"
#define SERVER_LINE_TERMINATOR_SIZE 1

// line: The line of the client
// length: The length of the line
// entries: The entries of the line (for the TAILQ list)
typedef struct line_s {
    char *buf;
    size_t len;
    TAILQ_ENTRY(line_s) entries;
} line_t;

// fd: The file descriptor of the client
// buffer: The buffer of the client
// needs_exit: Whether the client should be removed from the server
// lines: The lines of the client
// entries: The entries of the client (for the TAILQ list)
typedef struct server_client_s {
    int fd;
    char buffer[SERVER_CLIENT_BUFFER_SIZE];
    bool needs_exit;
    TAILQ_HEAD(line_list_s, line_s) lines;
    TAILQ_ENTRY(server_client_s) entries;
} server_client_t;

// fd: The file descriptor of the server
// max_fd: The maximum file descriptor that can be read from
// addr: The address of the server
// read_fds: The fd_set of file descriptors to read from
// write_fds: The fd_set of file descriptors to write to
// clients: The list of clients connected to the server
// blocking: Whether the server should block when reading from clients
typedef struct server_s {
    int fd;
    int max_fd;
    struct sockaddr_in addr;
    fd_set read_fds;
    fd_set write_fds;
    TAILQ_HEAD(server_client_list_s, server_client_s) clients;
    bool blocking;
} server_t;

/**
 * @brief Get the number of clients connected to the server.
 * @param server The server to get the number of clients from
 * @return The number of clients connected to the server
*/
size_t server_get_client_count(server_t *);

/**
 * @brief Remove a client from the server's client list, given its file
 * descriptor. Closes the file descriptor and frees the client's
 * buffer.
 * @param server The server to remove the client from
 * @param fd The file descriptor of the client to remove
 * @return true if the client was removed, false otherwise
*/
bool server_remove_client(server_t *, int);

/**
 * @brief Adds a client to the server's client list.
 * The client will be added at the start of the list and needs to have a
 * valid file descriptor.
 * This function won't set fds in the fd_sets.
 * @param server The server to add the client to
 * @param fd The file descriptor of the client to add
 * @return true if the client was added, false otherwise (malloc failed)
*/
bool server_add_client(server_t *, int);

/**
 * @brief Frees all the lines of a client.
 * @param client The client to free the lines of
*/
void server_clear_client_lines(server_client_t *);

/**
 * @brief Initialize a server, binds it to the given port and set it up to
 * listen for incoming connections.
 * @param server The server structure to initialize
 * @param port The port to listen on
 * @return 0 on success, the value of errno on failure
*/
int server_init(server_t *, unsigned short);

/**
 * @brief Destroy a server, free all its resources and closes
 * all its associated file descriptors (including the server's and clients').
 * @param server The server to destroy
 * @return 0 on success, the value of errno on failure
*/
int server_destroy(server_t *);

/**
 * @brief Run a single step of the server.
 * All the steps are, in order:
 * - Remove clients that need to exit
 * - Set read and write fd_sets to zero
 * - Accept new connections and add them to the client list
 * - Read from clients using the server_client_read function
 * @param server The server to run
 * @return 0 on success, the value of errno on failure
*/
int server_step(server_t *);

// WARNING : WRITE FUNCTIONS DOES NOT ADD LINE TERMINATORS TO THE DATA

/**
 * @brief Write data to a client. The data will be sent immediately, after a
 * call to select.
 * @param server The server the client is connected to
 * @param client The client to write to
 * @param data The data to write
 * @param size The size of the data to write
 * @return 0 on success, the value of errno on failure
*/
int server_client_write(server_t *, server_client_t *, const char *, size_t);

/**
 * @brief Write a string to a client. The string must be null-terminated.
 * The data will be sent immediately, after a call to select.
 * @param server The server the client is connected to
 * @param client The client to write to
 * @param string The string to write
 * @return 0 on success, the value of errno on failure
*/
int server_client_write_string(server_t *, server_client_t *, const char *);

/**
 * @brief Write data to a client, formatted like printf. The data will be sent
 * immediately, after a call to select.
 * @param server The server the client is connected to
 * @param client The client to write to
 * @param format The format string
 * @param ... The arguments to format
 * @return 0 on success, the value of errno on failure
*/
int server_client_printf(server_t *, server_client_t *, const char *, ...);

/**
 * @brief Read lines from a client. This function will call select and read
 * from the client's file descriptor while there is data to read. The lines
 * will be stored in the client's line list.
 * @param server The server the client is connected to
 * @param client The client to read from
 * @return 0 on success, the value of errno on failure
*/
int server_client_read_lines(server_t *, server_client_t *);

/**
 * @brief Gets the first line of a client and removes it from the list.
 * @param client The client to get the line from
 * @return The first line of the client, or NULL if the client has no lines
*/
line_t *server_client_pop_line(server_client_t *);

/**
 * @brief Gets the first line of a client.
 * @param client The client to get the line from
 * @return The first line of the client, or NULL if the client has no lines
*/
line_t *server_client_peek_line(server_client_t *);
