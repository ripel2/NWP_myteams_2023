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
#include "logging_server.h"
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
    if (args[1] == NULL || args[2] == NULL) {
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
        return true;
    }
    return false;
}

static void create_team(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    char team_uuid[37];
    char event_msg[512];
    data_t *team_data = NULL;

    remove_bad_char(args[2]);
    string_strip_delim(&args[1], '"');
    string_strip_delim(&args[2], '"');
    if (strlen(args[1]) - 1 > MAX_NAME_LENGTH ||
    strlen(args[2]) - 1 > MAX_DESCRIPTION_LENGTH) {
        server_client_write_string(server, client,
        "550 Name or description too long\n");
        return;
    }
    generate_uuid(team_uuid);
    team_data = init_data(args[1], args[2], "NULL", team_uuid);
    add_team_to_struct(team_data);
    server_client_printf(server, client, "150 \"%s\"\n", team_uuid);
    server_event_team_created(team_uuid, args[1], current_user->user_data->name);
    sprintf(event_msg, "client_event_team_created \"%s\" \"%s\" \"%s\"", team_uuid, args[1], args[2]);
    send_event_to_all_users(server, event_msg, client->fd);
}

void handle_create(server_t *server, server_client_t *client, char **args)
{
    user_t *current_user = get_user_logged_in(client);

    if (handle_base_errors(server, client, args, current_user))
        return;
    if (args[2] != NULL && current_user->context->user_context == NO_CONTEXT) {
        create_team(server, client, args, current_user);
    }
}
