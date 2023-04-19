/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** main functions for client
*/

#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void client_init_empty_values(client_t *client)
{
    FD_ZERO(&client->read_fds);
    FD_ZERO(&client->write_fds);
    client->server_closed = false;
    client->needs_exit = false;
    memset(&client->buffer, 0, sizeof(client->buffer));
    memset(&client->use_channel_uuid, 0, sizeof(client->use_channel_uuid));
    memset(&client->use_team_uuid, 0, sizeof(client->use_team_uuid));
    memset(&client->use_thread_uuid, 0, sizeof(client->use_thread_uuid));
}

int client_init(client_t *client, const char *ip, int port)
{
    client_init_empty_values(client);
    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    client->buffer_cur = 0;
    if (client->fd == -1)
        return errno;
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(port);
    client->addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(client->fd, (struct sockaddr *)&client->addr,
    sizeof(client->addr)) == -1)
        return errno;
    return (0);
}

void client_destroy(client_t *client)
{
    close(client->fd);
}
