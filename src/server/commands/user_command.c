/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** user_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "teams_commands.h"
#include "data.h"
#include "server.h"

static void display_user(server_t *server, server_client_t *client,
user_t *user)
{
    server_client_write_string(server, client, "150 ");
    server_client_write_string(server, client, user->user_data->uuid);
    server_client_write_string(server, client, " ");
    server_client_write_string(server, client, user->user_data->name);
    server_client_write_string(server, client, " ");
    server_client_write_string(server, client, (user->is_logged ? "1" : "0"));
    server_client_write_string(server, client, "\n");
}

void handle_user(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;

    if (args[1] == NULL) {
        server_client_write_string(server, client, "No arguments given\n");
        return;
    }
    remove_bad_char(args[1]);
    string_strip_delim(&args[1], '"');
    user = get_user_from_struct(args[1]);
    if (user == NULL) {
        server_client_write_string(server, client, "430 User doesn't exist\n");
        return;
    }
    display_user(server, client, user);
}
