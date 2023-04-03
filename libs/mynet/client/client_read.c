/*
** EPITECH PROJECT, 2023
** mynet/client
** File description:
** mynet client read functions
*/

#include "client.h"

/**
 * @brief Get the last line of the client
 * @param client The client
 * @return The last line of the client
*/
static line_t *server_client_get_last_line(client_t *client)
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
static int server_client_append_last_line(client_t *client,
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
static int server_client_append_split_line(client_t *client,
line_t *line, ssize_t ret, char *term)
{
    size_t len = term - client->buffer;

    if (server_client_append_last_line(client, line, len + 1) != 0)
        return ENOMEM;
    if (client->buffer + ret == term + CLIENT_LINE_TERMINATOR_SIZE)
        return 0;
    line = calloc(1, sizeof(line_t));
    if (line == NULL)
        return ENOMEM;
    line->buf = strdup(term + CLIENT_LINE_TERMINATOR_SIZE);
    line->len = strlen(line->buf);
    TAILQ_INSERT_TAIL(&client->lines, line, entries);
    return 0;
}

/**
 * @brief Add a chunk of data to the last line of the client
 * If it contains a newline, it will split the line, add the first part to the
 * last line and create a new line with the second part
*/
static int server_client_add_chunk(client_t *client, ssize_t ret)
{
    line_t *line = server_client_get_last_line(client);
    char *term = strstr(client->buffer, CLIENT_LINE_TERMINATOR);

    if (line == NULL)
        return ENOMEM;
    if (term == NULL) {
        return server_client_append_last_line(client, line, ret);
    } else {
        return server_client_append_split_line(client, line, ret, term);
    }
    return 0;
}

int client_read_lines(client_t *client)
{
    struct timeval timeout = {0, 0};
    int ret = 0;

    do {
        FD_ZERO(&client->read_fds);
        FD_SET(client->fd, &client->read_fds);
        ret = select(client->fd + 1, &client->read_fds, NULL, NULL, &timeout);
        if (ret < 0 && errno != EINTR)
            return errno;
        if (ret == 0) {
            client->needs_exit = true;
            break;
        }
        memset(client->buffer, 0, CLIENT_BUFFER_SIZE);
        ret = read(client->fd, client->buffer, CLIENT_BUFFER_SIZE);
        server_client_add_chunk(client, ret);
        FD_CLR(client->fd, &client->read_fds);
    } while (FD_ISSET(client->fd, &client->read_fds));
    FD_CLR(client->fd, &client->read_fds);
    return 0;
}
