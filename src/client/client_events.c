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

static int client_process_event_buffer(client_t *client, char *buffer)
{
    char *args[7] = {NULL};

    (void)client;
    split_string_fixed_array(buffer, args, 7);
    for (size_t c = 0; c < 7; c++)
        printf("args[%zu] = %s\n", c, args[c]);
    return 0;
}

int client_handle_event(client_t *client)
{
    char buffer[4097] = {0};
    size_t cur = 0;
    int ret = 0;

    do {
        FD_SET(client->fd, &client->read_fds);
        ret = select(client->fd + 1, &client->read_fds, NULL, NULL, NULL);
        if (ret < 0 && errno != EINTR)
            return errno;
        if (ret == 0) {
            client->needs_exit = true;
            break;
        }
        ret = read(client->fd, buffer + cur, 4096 - cur);
        cur += ret == - 1 ? 0 : ret;
        FD_CLR(client->fd, &client->read_fds);
    } while (ret > 0 && FD_ISSET(client->fd, &client->read_fds) && cur < 4096);
    FD_CLR(client->fd, &client->read_fds);
    return client_process_event_buffer(client, buffer);
}
