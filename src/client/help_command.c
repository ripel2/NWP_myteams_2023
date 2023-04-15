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

static int help_command_end(line_t *answer)
{
    write(1, answer->buf, answer->len);
    free(answer->buf);
    free(answer);
    return 0;
}

int help_command(client_t *client, client_info_t *info, char **args)
{
    char command[128] = {0};
    line_t *line = NULL;
    int ret = 0;

    (void)info;
    strcpy(command, "HELP");
    if (args[1] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
        strcat(command, "\n");
    }
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return help_command_end(line);
}
