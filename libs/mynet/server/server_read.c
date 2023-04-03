/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server read functions
*/

#include "server.h"

/**
 * @brief Get the last line of the client
 * @param client The client
 * @return The last line of the client
*/
static line_t *server_client_get_last_line(server_client_t *client)
{
    line_t *line = NULL;

    if (TAILQ_EMPTY(&client->lines)) {
        line = calloc(1, sizeof(line_t));
        line->buf = NULL;
        line->len = 0;
        TAILQ_INSERT_TAIL(&client->lines, line, entries);
    } else {
        line = TAILQ_LAST(&client->lines, line_list_s);
        if (line->len > 0 && line->buf[line->len - 1] == '\n') {
            line = calloc(1, sizeof(line_t));
            line->buf = NULL;
            line->len = 0;
            TAILQ_INSERT_TAIL(&client->lines, line, entries);
        }
    }
    return line;
}

/**
 * @brief Append a chunk of data to the last line of the client
 * @param client The client
 * @param line The last line of the client
 * @param ret The size of the chunk (return value of read)
 * @return 0 on success, an error code otherwise
*/
static int server_client_append_last_line(server_client_t *client,
line_t *line, ssize_t ret)
{
    line->buf = realloc(line->buf, line->len + ret + 1);
    if (line->buf == NULL)
        return ENOMEM;
    memset(line->buf + line->len, 0, ret + 1);
    memcpy(line->buf + line->len, client->buffer, ret);
    line->len += ret;
    return 0;
}

/**
 * @brief Append a chunk of data to the last line of the client and add
 * the remaining to a new line
 * @param client The client
 * @param line The last line of the client
 * @param ret The size of the chunk (return value of read)
 * @param term The position of the newline
*/
static int server_client_append_split_line(server_client_t *client,
line_t *line, ssize_t ret, char *term)
{
    size_t len = term - client->buffer;

    if (server_client_append_last_line(client, line, len + 1) != 0)
        return ENOMEM;
    if (client->buffer + ret == term + SERVER_LINE_TERMINATOR_SIZE)
        return 0;
    line = calloc(1, sizeof(line_t));
    if (line == NULL)
        return ENOMEM;
    line->buf = strdup(term + SERVER_LINE_TERMINATOR_SIZE);
    line->len = strlen(line->buf);
    TAILQ_INSERT_TAIL(&client->lines, line, entries);
    return 0;
}

/**
 * @brief Add a chunk of data to the last line of the client
 * If it contains a newline, it will split the line, add the first part to the
 * last line and create a new line with the second part
*/
static int server_client_add_chunk(server_client_t *client, ssize_t ret)
{
    line_t *line = server_client_get_last_line(client);
    char *term = strstr(client->buffer, SERVER_LINE_TERMINATOR);

    if (line == NULL)
        return ENOMEM;
    if (term == NULL) {
        return server_client_append_last_line(client, line, ret);
    } else {
        return server_client_append_split_line(client, line, ret, term);
    }
    return 0;
}

int server_client_read_lines(server_t *server, server_client_t *client)
{
    struct timeval timeout = {0, 0};
    int ret = 0;

    while (FD_ISSET(client->fd, &server->read_fds)) {
        memset(client->buffer, 0, SERVER_CLIENT_BUFFER_SIZE);
        ret = read(client->fd, client->buffer, SERVER_CLIENT_BUFFER_SIZE);
        if (ret == 0) {
            client->needs_exit = true;
            return 0;
        }
        server_client_add_chunk(client, ret);
        ret = select(client->fd + 1, &server->read_fds, NULL, NULL, &timeout);
        if (ret < 0 && errno != EINTR)
            return errno;
    }
    return 0;
}
