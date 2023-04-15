/*
** EPITECH PROJECT, 2023
** myteams_cli
** File description:
** myteams_cli command
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "shared.h"
#include "data.h"
#include "client.h"
#include "client_functions.h"

static int login_command_end(client_info_t *info, line_t *answer, char *name)
{
    write(1, answer->buf, answer->len);
    if (answer->buf[0] == '2') {
        memset(info->uuid, 0, UUID_LENGTH + 1);
        memcpy(info->uuid, answer->buf + 4, answer->len - 5);
        memset(info->username, 0, MAX_NAME_LENGTH + 1);
        memcpy(info->username, name, strlen(name));
        dll.functions[CLIENT_EVENT_LOGGED_IN](info->uuid, info->username);
    }
    free(answer->buf);
    free(answer);
    return 0;
}

int login_command(client_t *client, client_info_t *info, char **args)
{
    char command[128] = {0};
    line_t *line = NULL;
    int ret = 0;

    strcpy(command, "LOGIN");
    if (args[1] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return login_command_end(info, line, args[1]);
}
