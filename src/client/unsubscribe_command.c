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

static int unsubscribe_command_end(line_t *answer, char *user, char *team)
{
    write(1, answer->buf, answer->len);
    if (strncmp(answer->buf, "530", 3) == 0) {
        dll.functions[CLIENT_ERROR_UNAUTHORIZED]();
    } else if (strncmp(answer->buf, "200", 3) == 0) {
        dll.functions[CLIENT_PRINT_UNSUBSCRIBED](user, team);
    }
    if (strncmp(answer->buf, "430", 3) == 0 ||
    strncmp(answer->buf, "550", 3) == 0) {
        dll.functions[CLIENT_ERROR_UNKNOWN_TEAM]();
    }
    free(answer->buf);
    free(answer);
    return 0;
}

int unsubscribe_command(client_t *client, client_info_t *info, char **args)
{
    char command[128] = {0};
    line_t *line = NULL;
    int ret = 0;

    (void)info;
    strcpy(command, "UNSUBSCRIBE");
    if (args[1] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return unsubscribe_command_end(line, info->username, args[1]);
}
