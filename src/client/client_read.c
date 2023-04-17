/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** client main loop
*/

#include "client.h"
#include "client_functions.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int client_read_in_buffer(client_t *client)
{
    int ret = 0;

    do {
        FD_SET(client->fd, &client->read_fds);
        ret = select(client->fd + 1, &client->read_fds, NULL, NULL, NULL);
        if (ret < 0 && errno != EINTR)
            return errno;
        ret = read(client->fd, client->buffer + client->buffer_cur,
        CLIENT_BUFFER_SIZE - client->buffer_cur);
        if (ret == 0) {
            client->server_closed = true;
            break;
        }
        client->buffer_cur += ret == - 1 ? 0 : ret;
        FD_CLR(client->fd, &client->read_fds);
    } while (ret > 0 && FD_ISSET(client->fd, &client->read_fds)
    && client->buffer_cur < CLIENT_BUFFER_SIZE);
    FD_CLR(client->fd, &client->read_fds);
    return 0;
}

bool client_flush_line(client_t *client, char *line)
{
    for (size_t c = 0; c < client->buffer_cur; c++) {
        if (client->buffer[c] == '\n') {
            client->buffer[c] = '\0';
            strcpy(line, client->buffer);
            client->buffer_cur -= c + 1;
            memmove(client->buffer, client->buffer + c + 1,
            client->buffer_cur);
            memset(client->buffer + client->buffer_cur, 0, CLIENT_BUFFER_SIZE
            - client->buffer_cur);
            return true;
        }
    }
    return false;
}
