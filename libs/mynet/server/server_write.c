/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server write functions
*/

// Client writes are always non blocking because we don't want to block the
// server if one client is not available to write to, we just want to
// ignore it and continue with the others.

#include "server.h"

int server_client_write(server_t *server, server_client_t *client,
const char *str, size_t size)
{
    struct timeval tv = {0, 0};
    int ret = 0;

    FD_SET(client->fd, &server->write_fds);
    ret = select(client->fd + 1, NULL, &server->write_fds, NULL, &tv);
    if (ret == -1) {
        FD_CLR(client->fd, &server->write_fds);
        return errno;
    }
    if (FD_ISSET(client->fd, &server->write_fds)) {
        ret = write(client->fd, str, size);
        FD_CLR(client->fd, &server->write_fds);
        if (ret == -1)
            return errno;
    } else {
        return EAGAIN;
    }
    return 0;
}

int server_client_write_string(server_t *server, server_client_t *client,
const char *str)
{
    return server_client_write(server, client, str, strlen(str));
}

static int server_client_printf_avl(server_t *server, server_client_t *client,
const char *format, va_list args)
{
    int ret = 0;

    if (FD_ISSET(client->fd, &server->write_fds)) {
        ret = vdprintf(client->fd, format, args);
        FD_CLR(client->fd, &server->write_fds);
        if (ret == -1)
            return errno;
    } else
        return EAGAIN;
    return 0;
}

int server_client_printf(server_t *server, server_client_t *client,
const char *format, ...)
{
    struct timeval tv = {0, 0};
    va_list args;
    int ret = 0;

    va_start(args, format);
    FD_SET(client->fd, &server->write_fds);
    ret = select(client->fd + 1, NULL, &server->write_fds, NULL, &tv);
    if (ret == -1) {
        va_end(args);
        FD_CLR(client->fd, &server->write_fds);
        return errno;
    }
    return server_client_printf_avl(server, client, format, args);
}
