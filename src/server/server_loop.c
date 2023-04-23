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

static bool user_state_is_valid(int fd_tmp, server_t *server)
{
    server_client_t *client_tmp = NULL;
    bool found = false;

    TAILQ_FOREACH(client_tmp, &server->clients, entries) {
        if (fd_tmp == client_tmp->fd) {
            found = true;
            break;
        }
    }
    return found;
}

static void remove_all_disconnected_user(server_t *server)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user == NULL)
            continue;
        if (!user_state_is_valid(user->socket_fd, server)) {
            user->is_logged = false;
            user->socket_fd = -1;
        }
    }
}

int teams_server_loop(server_t *server)
{
    server_client_t *client = NULL;

    while (server_step(server) == 0) {
        remove_all_disconnected_user(server);
        TAILQ_FOREACH(client, &server->clients, entries) {
            teams_handle_client_commands(server, client);
        }
    }
    return 0;
}
