/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** create_tools
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void create_team(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    char team_uuid[37];
    char event_msg[2048];
    data_t *team_data = NULL;

    if (strlen(args[1]) - 1 > MAX_NAME_LENGTH ||
    strlen(args[2]) - 1 > MAX_DESCRIPTION_LENGTH) {
        server_client_write_string(server, client,
        "550 Name or description too long\n");
        return;
    }
    generate_uuid(team_uuid);
    team_data = init_data(args[1], args[2], "NULL", team_uuid);
    add_team_to_struct(team_data);
    server_client_printf(server, client, "200 \"%s\"\n", team_uuid);
    server_event_team_created(team_uuid, args[1],
    current_user->user_data->name);
    sprintf(event_msg, "client_event_team_created \"%s\" \"%s\" \"%s\"\n"
    , team_uuid, args[1], args[2]);
    send_event_to_all_users(server, event_msg, client->fd);
}

void create_channel(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    char channel_uuid[37];
    char event_msg[2048];
    data_t *channel_data = NULL;

    if (strlen(args[1]) - 1 > MAX_NAME_LENGTH ||
    strlen(args[2]) - 1 > MAX_DESCRIPTION_LENGTH) {
        server_client_write_string(server, client,
        "550 Name or description too long\n");
        return;
    }
    generate_uuid(channel_uuid);
    channel_data = init_data(args[1], args[2], "NULL", channel_uuid);
    add_channel_to_struct(current_user->context->team_uuid, channel_data);
    server_client_printf(server, client, "200 \"%s\"\n", channel_uuid);
    server_event_channel_created(current_user->context->team_uuid,
    channel_uuid, args[1]);
    sprintf(event_msg, "client_event_channel_created \"%s\" \"%s\" \"%s\"\n"
    , channel_uuid, args[1], args[2]);
    send_event_to_all_users(server, event_msg, client->fd);
}

static bool handle_args_length(server_t *server, server_client_t *client,
char **args)
{
    if (args[2] == NULL && strlen(args[1]) - 1 > MAX_BODY_LENGTH) {
        server_client_write_string(server, client,
        "550 Body too long\n");
        return true;
    }
    if (args[2] != NULL && (strlen(args[1]) - 1 > MAX_NAME_LENGTH ||
    strlen(args[2]) - 1 > MAX_DESCRIPTION_LENGTH)) {
        server_client_write_string(server, client,
        "550 Title or message too long\n");
        return true;
    }
    return false;
}

void create_thread(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    char thread_uuid[37];
    char event_msg[2048];
    data_t *thread_data = NULL;
    time_t t = time(NULL);

    if (handle_args_length(server, client, args))
        return;
    generate_uuid(thread_uuid);
    thread_data = init_data(args[1], args[2], "NULL", thread_uuid);
    add_thread_to_struct(current_user->context->channel_uuid,
    current_user->user_data, thread_data);
    server_client_printf(server, client, "200 \"%s\"\n", thread_uuid);
    server_event_thread_created(current_user->context->channel_uuid,
    thread_uuid, current_user->user_data->uuid, args[1], args[2]);
    sprintf(event_msg,
    "client_event_thread_created \"%s\" \"%s\" %ld \"%s\" \"%s\"\n"
    , thread_uuid, current_user->user_data->uuid, t, args[1], args[2]);
    send_event_to_all_users(server, event_msg, client->fd);
}

void create_reply(server_t *server, server_client_t *client
, char **args, user_t *current_user)
{
    char reply_uuid[37];
    char event_msg[2048];
    data_t *reply_data = NULL;

    if (handle_args_length(server, client, args))
        return;
    generate_uuid(reply_uuid);
    reply_data = init_data("NULL", "NULL", args[1], reply_uuid);
    add_reply_to_struct(current_user->context->thread_uuid,
    current_user->user_data, reply_data);
    server_client_printf(server, client, "200 \"%s\"\n", reply_uuid);
    server_event_reply_created
    (current_user->context->thread_uuid, current_user->user_data->uuid,
    args[1]);
    sprintf(event_msg,
    "client_event_reply_created \"%s\" \"%s\" \"%s\" \"%s\"\n"
    , current_user->context->team_uuid,
    current_user->context->thread_uuid, current_user->user_data->uuid, args[1]);
    send_event_to_all_users(server, event_msg, client->fd);
}
