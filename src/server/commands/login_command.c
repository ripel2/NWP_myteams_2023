/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** login_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"
#include "logging_server.h"

static user_t *get_user_from_struct_by_username(const char *username)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && strcmp(user->user_data->name, username) == 0) {
            return user;
        }
    }
    return user;
}

static bool handle_error_in_args(server_t *server,
server_client_t *client, char **args)
{
    if (args[1] == NULL || args[2] != NULL) {
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
        return true;
    }
    if (strlen(args[1]) > MAX_NAME_LENGTH) {
        server_client_write_string(server, client,
        "550 Username too long\n");
        return true;
    }
    return false;
}

static void create_user(server_t *server, server_client_t *client,
char **args, char *user_uuid)
{
    data_t *user_data = NULL;
    char user_uuid_with_quotes[40] = {0};
    char event_msg[512];

    string_strip_delim(&args[1], '"');
    strcat(user_uuid_with_quotes, "\"");
    strcat(user_uuid_with_quotes, user_uuid);
    strcat(user_uuid_with_quotes, "\"");
    server_event_user_created(user_uuid, args[1]);
    user_data = init_data(args[1], "NULL", "NULL", user_uuid);
    add_user_to_struct(user_data);
    get_user_from_struct(user_uuid)->is_logged = true;
    get_user_from_struct(user_uuid)->socket_fd = client->fd;
    server_event_user_logged_in(user_uuid);
    server_client_write_string(server, client, "230 ");
    server_client_write_string(server, client, user_uuid_with_quotes);
    server_client_write_string(server, client, " logged in\n");
    sprintf(event_msg, "client_event_logged_in %s %s\n", user_uuid, args[1]);
    send_event_to_all_users(server, event_msg, client->fd);
}

static void login_user(server_t *server, server_client_t *client,
char **args)
{
    user_t *user = NULL;
    char user_uuid_with_quotes[40] = {0};
    char event_msg[512];

    user = get_user_from_struct_by_username(args[1]);
    strcat(user_uuid_with_quotes, "\"");
    strcat(user_uuid_with_quotes, user->user_data->uuid);
    strcat(user_uuid_with_quotes, "\"");
    user->is_logged = true;
    user->socket_fd = client->fd;
    server_event_user_logged_in(user->user_data->uuid);
    server_client_write_string(server, client, "230 ");
    server_client_write_string(server, client, user_uuid_with_quotes);
    server_client_write_string(server, client, " logged in\n");
    sprintf(event_msg, "client_event_logged_in %s %s\n",
    user->user_data->uuid, user->user_data->name);
    send_event_to_all_users(server, event_msg, client->fd);
}

void handle_login(server_t *server, server_client_t *client, char **args)
{
    char user_uuid[37];
    user_t *user = NULL;

    if (handle_error_in_args(server, client, args) ||
    is_user_already_logged_in(server, client))
        return;
    remove_bad_char(args[1]);
    string_strip_delim(&args[1], '"');
    generate_uuid(user_uuid);
    user = get_user_from_struct_by_username(args[1]);
    if (user == NULL) {
        create_user(server, client, args, user_uuid);
        return;
    }
    if (user != NULL && user->is_logged == false) {
        login_user(server, client, args);
        return;
    } else if (user != NULL && user->is_logged == true) {
        server_client_write_string(server, client, "431 Already logged in\n");
        return;
    }
}
