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
    if (args[1] != NULL && is_a_uuid(args[1]) == false) {
        server_client_write_string(server, client, "550 Bad uuid\n");
        return true;
    }
    if (args[2] != NULL && is_a_uuid(args[2]) == false) {
        server_client_write_string(server, client, "550 Bad uuid\n");
        return true;
    }
    if (args[3] != NULL && is_a_uuid(args[3]) == false) {
        server_client_write_string(server, client, "550 Bad uuid\n");
        return true;
    }
    return false;
}

static void set_context(server_t *server, server_client_t *client,
char **args)
{
    if (args[1] == NULL) {
        set_no_context(server, client);
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

void handle_use(server_t *server, server_client_t *client, char **args)
{
    if (get_user_logged_in(client) == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    if (args[1] != NULL) {
        remove_bad_char(args[1]);
        string_strip_delim(&args[1], '"');
    }
    if (args[2] != NULL) {
        remove_bad_char(args[2]);
        string_strip_delim(&args[2], '"');
    }
    if (args[3] != NULL) {
        remove_bad_char(args[3]);
        string_strip_delim(&args[3], '"');
    }
    if (handle_error_in_args(server, client, args))
        return;
    set_context(server, client, args);
}
