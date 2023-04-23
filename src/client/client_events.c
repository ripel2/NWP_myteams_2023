/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** client main loop
*/

#include "client.h"
#include "client_functions.h"
#include "logging_client.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static const char *EVENT_STRINGS[] = {
    "client_event_private_message_received",
    "client_event_team_created",
    "client_event_channel_created",
    "client_event_thread_created",
    "client_event_thread_reply_received"
};

static void client_process_event_call(int event_id, char **args)
{
    switch (event_id) {
        case 0:
            client_event_private_message_received(args[1], args[2]);
            break;
        case 1:
            client_event_team_created(args[1], args[2], args[3]);
            break;
        case 2:
            client_event_channel_created(args[1], args[2], args[3]);
            break;
        case 3:
            client_event_thread_created(args[1], args[2],
            client_get_time_from_string(args[3]), args[4], args[5]);
            break;
        case 4:
            client_event_thread_reply_received(args[1], args[2], args[3],
            args[4]);
            break;
    }
}

static int client_process_event_buffer(client_t *client, char *buffer)
{
    char *args[7] = {NULL};
    int event_id = 0;

    (void)client;
    split_string_fixed_array(buffer, args, 7);
    for (event_id = 0; event_id < 5; event_id++) {
        if (strcmp(args[0], EVENT_STRINGS[event_id]) == 0) {
            break;
        }
    }
    if (event_id == 5)
        return 0;
    client_process_event_call(event_id, args);
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
