/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"
#include "server.h"

static int line_safe_strncmp(line_t *line, char *str2, size_t n)
{
    if (line->buf == NULL || line->len < n)
        return -1;
    return strncmp(line->buf, str2, n);
}

static void teams_handle_client(server_t *server, server_client_t *client)
{
    line_t *line = server_client_pop_line(client);

    if (line == NULL)
        return;
    if (line_safe_strncmp(line, "LOGIN", 4) == 0) {
        server_client_write_string(server, client, "PONG\n");
    }
}

int teams_server_loop(server_t *server)
{
    server_client_t *client = NULL;

    while (server_step(server) == 0) {
        TAILQ_FOREACH(client, &server->clients, entries) {
            teams_handle_client(server, client);
        }
    }
    return 0;
}

