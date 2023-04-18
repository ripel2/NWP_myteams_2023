/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** all_commands_array
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"
#include "teams_commands.h"

const char *COMMAND_NAME[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send", "/messages",
    "/subscribe", "/subscribed", "/unsubscribe", "/use", "/create", "/list",
    "/info", 0
};

void (*teams_commands[])() = {
    handle_help,
    handle_login,
    handle_logout,
    handle_users,
    handle_user,
    handle_send,
    handle_messages,
    handle_subscribe,
    handle_subscribed,
    handle_unsubscribe,
    handle_use,
    handle_create,
    handle_list,
    handle_info
};

static int line_safe_strncmp(char *str1, const char *str2, size_t n)
{
    if (str1 == NULL || strlen(str1) < n)
        return -1;
    return strncmp(str1, str2, n);
}

static bool user_state_is_valid(int fd_tmp, server_t *server)
{
    server_client_t *client_tmp = NULL;
    bool found = false;

    TAILQ_FOREACH(client_tmp, &server->clients, entries) {
        if (fd_tmp == client_tmp->fd) {
            found = true;
            break;
        }
    }
    return found;
}

static void remove_all_disconnected_user(server_t *server)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user == NULL)
            continue;
        if (!user_state_is_valid(user->socket_fd, server)) {
            user->is_logged = false;
            user->socket_fd = -1;
        }
    }
}

void teams_handle_client_commands(server_t *server, server_client_t *client)
{
    line_t *line = server_client_pop_line(client);
    char *command_parsed[7] = {NULL};
    bool found = false;

    remove_all_disconnected_user(server);
    if (line == NULL)
        return;
    split_string_fixed_array(line->buf, command_parsed, 7);
    if (command_parsed == NULL)
        return;
    for (int i = 0; COMMAND_NAME[i] != 0; i++) {
        if (line_safe_strncmp(command_parsed[0], COMMAND_NAME[i],
        strlen(COMMAND_NAME[i])) == 0) {
            teams_commands[i](server, client, command_parsed);
            found = true;
            break;
        }
    }
    if (!found)
        server_client_write_string(server, client, "500 Unknown command\n");
}
