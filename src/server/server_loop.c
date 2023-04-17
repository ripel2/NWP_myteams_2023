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
#include "teams_server.h"
#include "data.h"
#include "server.h"

int teams_server_loop(server_t *server)
{
    server_client_t *client = NULL;

    while (server_step(server) == 0) {
        TAILQ_FOREACH(client, &server->clients, entries) {
            teams_handle_client_commands(server, client);
        }
    }
    return 0;
}
