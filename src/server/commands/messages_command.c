/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** messages_command
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

static personal_discussion_t *get_discussion_between_user(user_t *current_user, user_t *user_to_seek) {
    personal_discussion_t *discussion = NULL;

    TAILQ_FOREACH(discussion, &current_user->discussions, entries) {
        if (discussion->user_data->uuid == user_to_seek->user_data->uuid) {
            return discussion;
        }
    }
    return NULL;
}

static void list_all_message_between_user(user_t *current_user, user_t *user_to_seek
, server_t *server, server_client_t *client) {
    personal_discussion_t *discussion = get_discussion_between_user(current_user, user_to_seek);
    message_t *message = NULL;

    if (discussion == NULL) {
        server_client_write_string(server, client, "430 No message between you and this user\n");
        return;
    }
    TAILQ_FOREACH(message, &discussion->messages, entries) {
        if (strcmp(message->user_data->uuid, current_user->user_data->uuid) == 0) {
            server_client_write_string(server, client, "TO ");
            server_client_write_string(server, client, message->message_data->body);
            server_client_write_string(server, client, "\n");
        }
        if (strcmp(message->user_data->uuid, user_to_seek->user_data->uuid) == 0) {
            server_client_write_string(server, client, "FROM ");
            server_client_write_string(server, client, message->message_data->body);
            server_client_write_string(server, client, "\n");
        }
    }
    server_client_write_string(server, client, "200 OK\n");
}

void handle_messages(server_t *server, server_client_t *client, char **args)
{
    user_t *user_to_seek = NULL;
    user_t *current_user = NULL;

    current_user = get_user_logged_in(client);
    if (current_user == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    } else if (args[1] == NULL || args[2] != NULL) {
        server_client_write_string(server, client, "432 Invalid arguments\n");
        return;
    }
    string_strip_delim(&args[1], '"');
    remove_bad_char(args[1]);
    user_to_seek = get_user_from_struct(args[1]);
    if (user_to_seek == NULL) {
        server_client_write_string(server, client, "430 User doesn't exist\n");
        return;
    }
    list_all_message_between_user(current_user, user_to_seek, server, client);
}
