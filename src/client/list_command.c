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

static int list_command_print_lines(client_t *client)
{
    line_t *line = NULL;
    int ret = 0;

    ret = client_get_line_timeout(client, &line);
    while (ret == 0) {
        write(1, line->buf, line->len);
        if (line->len > 0 && line->buf[0] != '2') {
            free(line->buf);
            free(line);
            return 0;
        }
        free(line->buf);
        free(line);
        line = NULL;
        ret = client_get_line_timeout(client, &line);
    }
    return ret;
}

static int list_command_end(client_t *client, line_t *answer)
{
    write(1, answer->buf, answer->len);
    if (answer->len > 0 && answer->buf[0] == '1') {
        list_command_print_lines(client);
    }
    free(answer->buf);
    free(answer);
    return 0;
}

int list_command(client_t *client, client_info_t *info, char **args)
{
    char command[128] = {0};
    line_t *line = NULL;
    int ret = 0;

    (void)info;
    strcpy(command, "LIST");
    if (args[1] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return list_command_end(client, line);
}