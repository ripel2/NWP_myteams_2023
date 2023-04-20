/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** set_teams_context
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

static bool is_error_found(server_t *server, server_client_t *client
, char **args)
{
    team_t *team = get_team_from_struct(args[1]);
    channel_t *channel = get_channel_from_struct(args[2]);
    thread_t *thread = get_thread_from_struct(args[3]);

    if (team == NULL) {
        server_client_write_string(server, client, "430 Team doesn't exist\n");
        return true;
    }
    if (channel == NULL) {
        server_client_write_string(server, client,
        "430 Channel doesn't exist or doesn't belong to team\n");
        return true;
    }
    if (thread == NULL) {
        server_client_write_string(server, client,
        "430 Thread doesn't exist or doesn't belong to channel\n");
        return true;
    }
    return false;
}

void set_thread_context(server_t *server, server_client_t *client,
char **args)
{
    user_t *user = get_user_logged_in(client);

    if (is_error_found(server, client, args))
        return;
    user->context->user_context = THREADS;
    user->context->team_uuid[0] = '\0';
    user->context->channel_uuid[0] = '\0';
    user->context->thread_uuid[0] = '\0';
    strcat(user->context->team_uuid, args[1]);
    strcat(user->context->channel_uuid, args[2]);
    strcat(user->context->thread_uuid, args[3]);
    server_client_write_string(server, client, "110 OK\n");
}
