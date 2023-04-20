/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** client main loop
*/

#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int client_printf(client_t *client, const char *format, ...)
{
    struct timeval tv = {0, 0};
    int ret = 0;
    va_list args;

    FD_SET(client->fd, &client->write_fds);
    ret = select(client->fd + 1, NULL, &client->write_fds, NULL, &tv);
    if (ret == -1) {
        FD_CLR(client->fd, &client->write_fds);
        return errno;
    }
    if (FD_ISSET(client->fd, &client->write_fds)) {
        va_start(args, format);
        ret = vdprintf(client->fd, format, args);
        va_end(args);
        FD_CLR(client->fd, &client->write_fds);
        if (ret == -1)
            return errno;
    } else
        return EAGAIN;
    return 0;
}
