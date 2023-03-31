/*
** EPITECH PROJECT, 2023
** mynet/client
** File description:
** destroy a client
*/

#include "client.h"

void client_destroy(client_t *client)
{
    line_t *line = NULL;

    if (client->fd > 0)
        close(client->fd);
    while (!TAILQ_EMPTY(&client->lines)) {
        line = TAILQ_FIRST(&client->lines);
        TAILQ_REMOVE(&client->lines, line, entries);
        free(line->buf);
        free(line);
    }
}
