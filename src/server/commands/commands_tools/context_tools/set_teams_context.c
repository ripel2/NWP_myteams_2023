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

void set_teams_context(server_t *server, server_client_t *client,
char **args)
{
    user_t user = get_user_logged_in(server, client->fd);
    team_t *team = get_team_by_uuid(server, args[1]);

    if (team == NULL) {
        server_client_write_string(server, client, "430 Team doesn't exist\n");
        return;
    }
    new_user->context->user_context = TEAM_CONTEXT;
    new_user->context->team_uuid[0] = '\0';
    new_user->context->channel_uuid[0] = '\0';
    new_user->context->thread_uuid[0] = '\0';
    strcat(new_user->context->team_uuid, args[1]);
    server_client_write_string(server, client, "110 OK");
}
