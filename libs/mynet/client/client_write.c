/*
** EPITECH PROJECT, 2023
** mynet/client
** File description:
** mynet client
*/

#include "client.h"

int client_write(client_t *client, const char *buf, size_t size)
{
    struct timeval tv = {0, 0};
    int ret = 0;

    FD_SET(client->fd, &client->write_fds);
    ret = select(client->fd + 1, NULL, &client->write_fds, NULL, &tv);
    if (ret == -1) {
        FD_CLR(client->fd, &client->write_fds);
        return errno;
    }
    if (FD_ISSET(client->fd, &client->write_fds)) {
        ret = write(client->fd, buf, size);
        FD_CLR(client->fd, &client->write_fds);
        if (ret == -1)
            return errno;
    } else {
        return EAGAIN;
    }
    return 0;
}

int client_write_string(client_t *client, const char *str)
{
    return client_write(client, str, strlen(str));
}

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
