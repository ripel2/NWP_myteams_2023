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

static int use_command_end(line_t *answer)
{
    write(1, answer->buf, answer->len);
    if (strncmp(answer->buf, "530", 3) == 0) {
        dll.functions[CLIENT_ERROR_UNAUTHORIZED]();
    }
    free(answer->buf);
    free(answer);
    return 0;
}

int use_command(client_t *client, client_info_t *info, char **args)
{
    char command[1024] = {0};
    line_t *line = NULL;
    int ret = 0;
    size_t arg_count = 0;

    (void)info;
    strcpy(command, "USE");
    for (size_t c = 1; c < 4; c++) {
        if (args[c] != NULL) {
            strcat(command, " ");
            strcat(command, args[c]);
            arg_count++;
        }
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return use_command_end(line);
}
