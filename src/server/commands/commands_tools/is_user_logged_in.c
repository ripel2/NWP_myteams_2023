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
    server_client_t *client_tmp = NULL;

    TAILQ_FOREACH(client_tmp, &server->clients, entries) {
        if (fd_tmp == client_tmp->fd) {
            server_client_write_string(server, client,
            "431 Already logged in\n");
            return true;
        }
    }
    return false;
}

bool is_user_already_logged_in(server_t *server, server_client_t *client)
{
    user_t *tmp_user;
    bool return_value = false;

    TAILQ_FOREACH(tmp_user, &global->users, entries) {
        if (tmp_user && tmp_user->is_logged == true) {
            return_value = check_in_clients_fd(server,
            client, tmp_user->socket_fd);
        }
    }
    return return_value;
}
