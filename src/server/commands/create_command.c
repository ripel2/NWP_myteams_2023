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
    if (args[1] == NULL) {
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
        return true;
    }
    return false;
}

static void prepare_string(char **args)
{
    
        remove_bad_char(args[2]);
        string_strip_delim(&args[1], '"');
        string_strip_delim(&args[2], '"');
}

static bool handle_no_context_teams(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    if (args[2] != NULL && current_user->context->user_context == NO_CONTEXT) {
        prepare_string(args);
        create_team(server, client, args, current_user);
        return true;
    }
    if (current_user->context->user_context != NO_CONTEXT &&
    is_user_in_team(current_user, args[1]) == false) {
        server_client_write_string(server, client,
        "403 You are not in this team\n");
        return true;
    }
    if (args[2] != NULL && current_user->context->user_context == TEAMS) {
        prepare_string(args);
        create_channel(server, client, args, current_user);
        return true;
    }
    return false;
}

static bool handle_create_mode(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    if (handle_no_context_teams(server, client, args, current_user))
        return true;
    if (args[2] != NULL && current_user->context->user_context == CHANNELS) {
        remove_bad_char(args[2]);
        string_strip_delim(&args[1], '"');
        string_strip_delim(&args[2], '"');
        create_thread(server, client, args, current_user);
        return true;
    }
    if (args[2] == NULL && current_user->context->user_context == THREADS) {
        remove_bad_char(args[1]);
        string_strip_delim(&args[1], '"');
        create_reply(server, client, args, current_user);
        return true;
    }
    return false;
}

void handle_create(server_t *server, server_client_t *client, char **args)
{
    user_t *current_user = get_user_logged_in(client);

    if (handle_base_errors(server, client, args, current_user))
        return;
    if (handle_create_mode(server, client, args, current_user) == false)
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
}
