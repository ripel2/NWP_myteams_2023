/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** users_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void handle_users(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;
    int nb_users = 0;

    if (args[1] != NULL) {
        server_client_write_string(server, client, "501 Too many arguments\n");
        return;
    }
    TAILQ_FOREACH(user, &global->users, entries) {
        nb_users++;
    }
    server_client_printf(server, client, "150 %d\n", nb_users);
    TAILQ_FOREACH(user, &global->users, entries) {
        server_client_printf(server, client, "%s \"%s\" %c\n",
        user->user_data->uuid, user->user_data->name,
        (user->is_logged) ? '1' : '0');
    }
    server_client_write_string(server, client, "200 OK\n");
}
