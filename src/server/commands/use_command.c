/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** use_command
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

static bool handle_error_in_args(server_t *server, server_client_t *client,
char **args)
{
    if (args[4] != NULL) {
        return true;
    }
    if (args[1] != NULL) {
         if (is_a_uuid(args[1]) == false) {
            return true;
         }
    }
    if (args[2] != NULL) {
        if (is_a_uuid(args[2]) == false) {
            return true;
        }
    }
    if (args[3] != NULL) {
        if (is_a_uuid(args[3]) == false) {
            return true;
        }
    }
    return false;
}

void handle_use(server_t *server, server_client_t *client, char **args)
{
    if (handle_error_in_args(server, client, args) ||
    is_user_already_logged_in(server, client))
        return;
    if (args[1] == NULL) {
        set_no_context(server, client, args);
        return;
    }
    if (args[2] == NULL) {
        set_teams_context(server, client, args);
        return;
    }
    if (args[3] == NULL) {
        set_channel_context(server, client, args);
        return;
    }
    if (args[4] == NULL) {
        set_thread_context(server, client, args);
        return;
    }
}
