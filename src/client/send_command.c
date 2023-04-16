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

static void send_command_error_debug(line_t *line, char **args)
{
    if (strncmp(line->buf, "530", 3) == 0)
        dll.functions[CLIENT_ERROR_UNAUTHORIZED]();
    else if (strncmp(line->buf, "430", 3) == 0 ||
    strncmp(line->buf, "550", 3) == 0)
        dll.functions[CLIENT_ERROR_UNKNOWN_USER](args[1]);
}

static int send_command_cleanup(client_t *client, char **args,
client_info_t *info)
{
    line_t *line = NULL;

    client_get_line_timeout(client, &line);
    if (line == NULL)
        return -1;
    write(1, line->buf, line->len);
    if (strncmp(line->buf, "200", 3) == 0)
        dll.functions[CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED](info->username,
        args[2]);
    free(line->buf);
    free(line);
    return 0;
}

static int send_command_end(client_t *client, line_t *line, char **args,
client_info_t *info)
{
    int ret = 0;
    char *msgline = NULL;

    if (line->len > 0 && line->buf[0] != '3') {
        write(1, line->buf, line->len);
        send_command_error_debug(line, args);
        return 0;
    }
    msgline = strtok(args[2], "\n");
    while (msgline != NULL) {
        ret = client_write_string(client, msgline);
        if (ret != 0)
            return ret;
        ret = client_write_string(client, "\n");
        if (ret != 0)
            return ret;
        msgline = strtok(NULL, "\n");
    }
    return send_command_cleanup(client, args, info);
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
    return send_command_end(client, line, args, info);
}
