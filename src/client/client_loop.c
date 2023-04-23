/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** client main loop
*/

#include "client.h"
#include "client_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void client_print_exit_reason(client_t *client)
{
    if (client->needs_exit)
        printf("Client exiting...\n");
    else if (client->server_closed)
        printf("Server closed connection\n");
}

static void client_flush_remaining_buffer(client_t *client)
{
    char line[2048] = {0};

    while (client_flush_line(client, line)) {
        client_process_event_buffer(client, line);
    }
}

int client_loop(client_t *client)
{
    int ret = 0;

    while (!client->needs_exit && !client->server_closed) {
        FD_SET(STDIN_FILENO, &client->read_fds);
        FD_SET(client->fd, &client->read_fds);
        ret = select(client->fd + 1, &client->read_fds, NULL, NULL, NULL);
        if (ret < 0 && errno != EINTR)
            return errno;
        if (FD_ISSET(client->fd, &client->read_fds))
            client_handle_event(client);
        if (FD_ISSET(STDIN_FILENO, &client->read_fds))
            client_handle_command(client);
        FD_CLR(client->fd, &client->read_fds);
        FD_CLR(STDIN_FILENO, &client->read_fds);
        client_flush_remaining_buffer(client);
    }
    client_print_exit_reason(client);
    client_destroy(client);
    return 0;
}
