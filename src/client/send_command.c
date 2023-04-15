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

static int send_command_cleanup(client_t *client)
{
    line_t *line = NULL;

    client_get_line_timeout(client, &line);
    if (line == NULL)
        return -1;
    write(1, line->buf, line->len);
    free(line->buf);
    free(line);
    return 0;
}

static int send_command_end(client_t *client, line_t *line, char *msg)
{
    int ret = 0;
    char *msgline = NULL;

    if (line->len > 0 && line->buf[0] != '3') {
        write(1, line->buf, line->len);
        return 0;
    }
    msgline = strtok(msg, "\n");
    while (msgline != NULL) {
        ret = client_write_string(client, msgline);
        if (ret != 0)
            return ret;
        ret = client_write_string(client, "\n");
        if (ret != 0)
            return ret;
        msgline = strtok(NULL, "\n");
    }
    return send_command_cleanup(client);
}

int send_command(client_t *client, client_info_t *info, char **args)
{
    char command[1024] = {0};
    line_t *line = NULL;
    int ret = 0;

    (void)info;
    strcpy(command, "SEND");
    if (args[1] != NULL && args[2] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
        strcat(command, " ");
        strcat(command, "1");
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return send_command_end(client, line, args[2]);
}
