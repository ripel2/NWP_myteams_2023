/*
** EPITECH PROJECT, 2023
** mynet/client
** File description:
** mynet client line list
*/

#include "client.h"

line_t *client_pop_line(client_t *client)
{
    line_t *line = NULL;

    if (TAILQ_EMPTY(&client->lines))
        return NULL;
    line = TAILQ_FIRST(&client->lines);
    TAILQ_REMOVE(&client->lines, line, entries);
    return line;
}

line_t *client_peek_line(client_t *client)
{
    line_t *line = NULL;

    if (TAILQ_EMPTY(&client->lines))
        return NULL;
    line = TAILQ_FIRST(&client->lines);
    return line;
}
