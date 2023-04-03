/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server line list operations (pop, peek)
*/

#include "server.h"

line_t *server_client_pop_line(server_client_t *server)
{
    line_t *line = NULL;

    if (TAILQ_EMPTY(&server->lines))
        return NULL;
    line = TAILQ_FIRST(&server->lines);
    TAILQ_REMOVE(&server->lines, line, entries);
    return line;
}

line_t *server_client_peek_line(server_client_t *server)
{
    line_t *line = NULL;

    if (TAILQ_EMPTY(&server->lines))
        return NULL;
    line = TAILQ_FIRST(&server->lines);
    return line;
}
