/*
** EPITECH PROJECT, 2023
** myteams_cli
** File description:
** myteams_cli command
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "shared.h"
#include "data.h"
#include "client.h"
#include "client_functions.h"

static int execute_simple_command_timeout(client_t *client, line_t **result)
{
    int ret = 0;
    size_t retries = 0;
    size_t sleep = 1000;

    do {
        ret = client_read_lines(client);
        if (ret != 0)
            return ret;
        *result = client_pop_line(client);
        if (*result == NULL) {
            usleep(sleep);
            sleep *= 2;
            retries++;
        }
    } while (*result == NULL && retries < 14);
    if (*result == NULL)
        return -1;
    return 0;
}

int execute_simple_command(client_t *client, char *cmd,
size_t size, line_t **result)
{
    int ret = 0;

    ret = client_write(client, cmd, size);
    if (ret != 0)
        return ret;
    *result = NULL;
    return execute_simple_command_timeout(client, result);
}
