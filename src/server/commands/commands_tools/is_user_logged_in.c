/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_user_logged_in
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

static bool check_in_clients_fd(server_t *server, server_client_t *client,
int fd_tmp)
{
    if (fd_tmp == client->fd) {
        server_client_write_string(server, client, "431 Already logged in\n");
        return true;
    }
    return false;
}

bool is_user_already_logged_in(server_t *server, server_client_t *client)
{
    user_t *tmp_user = NULL;

    TAILQ_FOREACH(tmp_user, &global->users, entries) {
        if (tmp_user && tmp_user->is_logged == true && check_in_clients_fd(
            server, client, tmp_user->socket_fd)) {
            return true;
        }
    }
    return false;
}
