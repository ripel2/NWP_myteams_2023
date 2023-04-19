/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** logout_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

static user_t *get_user_logged_in(server_client_t *client)
{
    user_t *user;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && user->is_logged == true && user->socket_fd == client->fd) {
            return user;
        }
    }
    return user;
}

void handle_logout(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;
    char user_uuid_with_quotes[40] = {0};

    if (args[1] != NULL) {
        server_client_write_string(server, client, "501 Too many arguments\n");
        return;
    }
    user = get_user_logged_in(client);
    if (user == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    user->is_logged = false;
    user->socket_fd = -1;
    strcat(user_uuid_with_quotes, "\"");
    strcat(user_uuid_with_quotes, user->user_data->uuid);
    strcat(user_uuid_with_quotes, "\"");
    server_client_write_string(server, client, "221 ");
    server_client_write_string(server, client, user_uuid_with_quotes);
    server_client_write_string(server, client, " logged out\n");
}
