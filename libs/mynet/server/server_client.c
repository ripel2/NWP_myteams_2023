/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server clients functions
*/

#include "server.h"

size_t server_get_client_count(server_t *server)
{
    server_client_t *client = NULL;
    size_t count = 0;

    TAILQ_FOREACH(client, &server->clients, entries) {
        count++;
    }
    return (count);
}

void server_clear_client_lines(server_client_t *client)
{
    line_t *line = NULL;

    while (!TAILQ_EMPTY(&client->lines)) {
        line = TAILQ_FIRST(&client->lines);
        TAILQ_REMOVE(&client->lines, line, entries);
        free(line->buf);
        free(line);
    }
}

bool server_remove_client(server_t *server, int fd)
{
    server_client_t *client = NULL;

    TAILQ_FOREACH(client, &server->clients, entries) {
        if (client->fd == fd) {
            close(fd);
            TAILQ_REMOVE(&server->clients, client, entries);
            free(client);
            return true;
        }
    }
    return false;
}

bool server_add_client(server_t *server, int fd)
{
    server_client_t *client = calloc(1, sizeof(server_client_t));

    if (!client)
        return false;
    client->fd = fd;
    TAILQ_INIT(&client->lines);
    memset(client->buffer, 0, sizeof(client->buffer));
    TAILQ_INSERT_TAIL(&server->clients, client, entries);
    return true;
}
