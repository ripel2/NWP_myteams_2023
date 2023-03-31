/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server destroy function
*/

#include "server.h"

int server_destroy(server_t *server)
{
    int server_fd = server->fd;
    server_client_t *client = NULL;

    while (!TAILQ_EMPTY(&server->clients)) {
        client = TAILQ_FIRST(&server->clients);
        TAILQ_REMOVE(&server->clients, client, entries);
        close(client->fd);
        server_clear_client_lines(client);
        free(client);
    }
    return close(server_fd);
}
