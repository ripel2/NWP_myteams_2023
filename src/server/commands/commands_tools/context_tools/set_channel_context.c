/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** set_channel_context
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void set_channel_context(server_t *server, server_client_t *client,
char **args)
{
    user_t *user = get_user_logged_in(client);
    team_t *team = get_team_from_struct(args[1]);
    channel_t *channel = get_channel_from_struct(args[2]);

    if (team == NULL) {
        server_client_write_string(server, client, "430 Team doesn't exist\n");
        return;
    }
    if (channel == NULL) {
        server_client_write_string(server, client,
        "430 Channel doesn't exist or doesn't belong to team\n");
        return;
    }
    user->context->user_context = CHANNELS;
    user->context->team_uuid[0] = '\0';
    user->context->channel_uuid[0] = '\0';
    user->context->thread_uuid[0] = '\0';
    strcat(user->context->team_uuid, args[1]);
    strcat(user->context->channel_uuid, args[2]);
    server_client_write_string(server, client, "110 OK\n");
}
