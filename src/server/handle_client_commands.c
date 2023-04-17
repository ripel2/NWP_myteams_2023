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
    if (str1 == NULL ||  strlen(str1) < n)
        return -1;
    return strncmp(str1, str2, n);
}

static int get_nb_args(char *str, char *delim)
{
    int nb_args = 0;
    char *token = NULL;
    char *tmp = strdup(str);

    
    token = strtok(tmp, delim);
    for (int i = 0; token != NULL; i++) {
        token = strtok(NULL, delim);
        nb_args++;
    }
    free(tmp);
    return nb_args;
}

static char **split_line(char *str, char *delim)
{
    char **command_parsed = NULL;
    char *token = NULL;

    if (str == NULL)
        return NULL;
    command_parsed = malloc(sizeof(char *) * (get_nb_args(str, delim) + 1));
    token = strtok(str, delim);
    for (int i = 0; token != NULL; i++) {
        command_parsed[i] = strdup(token);
        token = strtok(NULL, delim);
    }
    return command_parsed;
}

static void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void teams_handle_client_commands(server_t *server, server_client_t *client)
{
    line_t *line = server_client_pop_line(client);
    char **command_parsed = NULL;
    bool found = false;

    if (line == NULL)
        return;
    command_parsed = split_line(line->buf, " ");
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
        server_client_write_string(server, client, "500 Unknown command");
    free_array(command_parsed);
}
