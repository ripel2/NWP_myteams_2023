/*
** EPITECH PROJECT, 2023
** myteams_cli
** File description:
** myteams_cli main function
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "shared.h"
#include "data.h"
#include "client.h"
#include "client_functions.h"

static const command_t COMMANDS[] = {
    {"/help", &help_command},
    {"/login", &login_command},
    {"/logout", &logout_command},
    {"/users", &users_command},
    {"/user", &user_command},
    {"/send", &send_command},
    {"/messages", &messages_command},
    {"/subscribe", &subscribe_command},
    {"/subscribed", &subscribed_command},
    {"/unsubscribe", &unsubscribe_command},
    {"/use", &use_command},
    {"/create", &create_command},
    {"/list", &list_command},
    {"/info", &info_command},
    {NULL, NULL}
};

void split_command_fixed_array(char *command, char **args, size_t size)
{
    char *token = strtok(command, " ");
    size_t c = 0;

    for (c = 0; c < size - 1; c++) {
        if (token == NULL)
            break;
        args[c] = token;
        token = strtok(NULL, " ");
    }
    args[c] = NULL;
}

int teams_start_command(client_t *client, client_info_t *info, char **command)
{
    for (size_t c = 0; COMMANDS[c].name != NULL; c++) {
        if (command[0] == NULL)
            return 0;
        if (strcmp(command[0], COMMANDS[c].name) == 0)
            return COMMANDS[c].func(client, info, command);
    }
    puts("500 Unknown command.");
    return 0;
}

ssize_t teams_getline(char **line, size_t *len, FILE *stream)
{
    ssize_t ret = 0;

    write(1, "myteams> ", 9);
    ret = getline(line, len, stream);
    if (ret > 0 && (*line)[ret - 1] == '\n')
        (*line)[ret - 1] = '\0';
    return ret;
}

int teams_client_loop(client_t *client)
{
    client_info_t info = {0};
    char *line = NULL;
    char args[7][1024] = {0};
    size_t len = 0;
    ssize_t read = teams_getline(&line, &len, stdin);
    int ret = 0;

    while (read != -1) {
        split_command_fixed_array(line, (char **)args, 7);
        ret = teams_start_command(client, &info, (char **)args);
        if (ret != 0)
            break;
        read = teams_getline(&line, &len, stdin);
    }
    free(line);
    return ret == 0 ? 0 : 84;
}
