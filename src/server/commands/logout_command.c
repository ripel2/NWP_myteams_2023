/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** logout_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "logging_server.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "teams_commands.h"
#include "data.h"
#include "server.h"

static void set_user_uuid_quotes(char *user_uuid_with_quotes, user_t *user)
{
    strcat(user_uuid_with_quotes, "\"");
    strcat(user_uuid_with_quotes, user->user_data->uuid);
    strcat(user_uuid_with_quotes, "\"");
}

static void send_logout_event(server_t *server, server_client_t *client
, user_t *user)
{
    char event_msg[512] = {0};

    server_event_user_logged_out(user->user_data->uuid);
    sprintf(event_msg, "client_event_logged_out  %s %s\n",
    user->user_data->uuid, user->user_data->name);
    send_event_to_all_users(server, event_msg, client->fd);
}

void handle_logout(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;
    char user_uuid_with_quotes[40] = {0};

    if (args[1] != NULL) {
        server_client_write_string(server, client, "501 Too many arguments\n");
        return;
    }
    user = get_user_logged_in(client);
    if (user == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    user->is_logged = false;
    user->socket_fd = -1;
    set_user_uuid_quotes(user_uuid_with_quotes, user);
    server_client_write_string(server, client, "221 ");
    server_client_write_string(server, client, user_uuid_with_quotes);
    server_client_write_string(server, client, " logged out\n");
    server_remove_client(server, client->fd);
    send_logout_event(server, client, user);
}
