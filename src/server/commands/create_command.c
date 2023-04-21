/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** create_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"
#include "teams_commands.h"

static bool handle_base_errors(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    if (current_user == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return true;
    }
    if (args[1] == NULL) {
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
        return true;
    }
    return false;
}

void handle_create(server_t *server, server_client_t *client, char **args)
{
    user_t *current_user = get_user_logged_in(client);

    if (handle_base_errors(server, client, args, current_user))
        return;
    if 
}
