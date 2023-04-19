/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** send_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

static user_t *get_user_from_struct_by_fd(int fd)
{
    user_t *tmp_user = NULL;

    TAILQ_FOREACH(tmp_user, &global->users, entries) {
        if (tmp_user && tmp_user->socket_fd == fd) {
            return tmp_user;
        }
    }
    return NULL;
}

static bool check_if_user_need_discussion(user_t *current_user, char *user_to_send_uuid)
{
    personal_discussion_t *tmp_discussion = NULL;

    TAILQ_FOREACH(tmp_discussion, &current_user->discussions, entries) {
        if (strcmp(tmp_discussion->user_data->uuid, user_to_send_uuid) == 0) {
            return false;
        }
    }
    return true;
}

static void create_new_discussion(user_t *current_user, char *user_to_send_uuid)
{
    char new_uuid[37];

    generate_uuid(new_uuid);
    add_personnal_discussion_to_struct(new_uuid, current_user->user_data->uuid, get_user_from_struct(user_to_send_uuid)->user_data);
    add_personnal_discussion_to_struct(new_uuid, user_to_send_uuid, current_user->user_data);
}

static void add_message_to_both_users(user_t *current_user, char *user_to_send_uuid, char *message)
{
    personal_discussion_t *tmp_discussion = NULL;
    data_t *discussion_uuid = NULL;
    data_t *message_data = init_data("", "", message, "");

    TAILQ_FOREACH(tmp_discussion, &current_user->discussions, entries) {
        if (strcmp(tmp_discussion->user_data->uuid, user_to_send_uuid) == 0) {
            discussion_uuid = init_data("", "", "", tmp_discussion->uuid);
            add_message_to_struct(current_user->user_data, discussion_uuid, message_data);
            break;
        }
    }
    TAILQ_FOREACH(tmp_discussion, &get_user_from_struct(user_to_send_uuid)->discussions, entries) {
        if (strcmp(tmp_discussion->user_data->uuid, current_user->user_data->uuid) == 0) {
            discussion_uuid = init_data("", "", "", tmp_discussion->uuid);
            add_message_to_struct(get_user_from_struct(user_to_send_uuid)->user_data, discussion_uuid, message_data);
            break;
        }
    }
}

static void send_message_to_user(server_t *server, server_client_t *client,
char *user_to_send_uuid, char *message)
{
    user_t *current_user = NULL;

    current_user = get_user_from_struct_by_fd(client->fd);
    if (current_user == NULL || current_user->is_logged == false) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    if (check_if_user_need_discussion(current_user, user_to_send_uuid) == true) {
        create_new_discussion(current_user, user_to_send_uuid);
    }
    add_message_to_both_users(current_user, user_to_send_uuid, message);
    server_client_write_string(server, client, "200 OK\n");
    server_event_private_message_sended(current_user->user_data->uuid, user_to_send_uuid, message);
}

static user_t *get_user_logged_in(server_client_t *client)
{
    user_t *user;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && user->is_logged == true && user->socket_fd == client->fd) {
            return user;
        }
    }
    return user;
}

void handle_send(server_t *server, server_client_t *client, char **args)
{
    if (get_user_logged_in(client) == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL) {
        server_client_write_string(server, client, "432 Invalid arguments\n");
        return;
    }
    string_strip_delim(&args[1], '"');
    string_strip_delim(&args[2], '"');
    remove_bad_char(args[1]);
    remove_bad_char(args[2]);
    if (get_user_from_struct(args[1]) == NULL) {
        server_client_write_string(server, client, "430 User doesn't exist\n");
        return;
    }
    send_message_to_user(server, client, args[1], args[2]);
}
