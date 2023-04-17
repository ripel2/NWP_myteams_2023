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
    int ret = 0;
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    while (client_flush_line(client, line)) {
        ret = client_process_event_buffer(client, line);
        if (ret != 0)
            return ret;
    }
    return 0;
}
