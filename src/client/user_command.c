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

static void user_command_call_debug_success(line_t *answer)
{
    char uuid[UUID_LENGTH + 1] = {0};
    char username[MAX_NAME_LENGTH + 1] = {0};
    int is_logged_in = 0;
    char *format = "150 %36s %32s %d";

    if (sscanf(answer->buf, format, uuid, username, &is_logged_in) == 3) {
        dll.functions[CLIENT_PRINT_USER](uuid, username, is_logged_in);
    }
}

static int user_command_end(line_t *answer, char *uuid)
{
    write(1, answer->buf, answer->len);
    if (strncmp(answer->buf, "530", 3) == 0) {
        dll.functions[CLIENT_ERROR_UNAUTHORIZED]();
    } else if (strncmp(answer->buf, "430", 3) == 0 ||
    strncmp(answer->buf, "550", 3) == 0) {
        dll.functions[CLIENT_ERROR_UNKNOWN_USER](uuid);
    }
    user_command_call_debug_success(answer);
    free(answer->buf);
    free(answer);
    return 0;
}

int user_command(client_t *client, client_info_t *info, char **args)
{
    char command[128] = {0};
    line_t *line = NULL;
    int ret = 0;

    (void)info;
    strcpy(command, "USER");
    if (args[1] != NULL) {
        strcat(command, " ");
        strcat(command, args[1]);
    }
    strcat(command, "\n");
    ret = execute_simple_command(client, command, strlen(command), &line);
    if (ret != 0)
        return ret;
    return user_command_end(line, args[1]);
}
