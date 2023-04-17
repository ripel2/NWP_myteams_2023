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

int client_init(client_t *client, const char *ip, int port)
{
    FD_ZERO(&client->read_fds);
    FD_ZERO(&client->write_fds);
    client->needs_exit = false;
    client->fd = socket(AF_INET, SOCK_STREAM, 0);
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
