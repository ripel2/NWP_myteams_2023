/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_thread_in_team
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>

bool is_thread_in_channel(const char *thread_uuid, const char *channel_uuid)
{
    channel_t *channel = get_channel_from_struct(channel_uuid);
    thread_t *thread = NULL;

    if (channel == NULL || get_thread_from_struct(thread_uuid) == NULL)
        return (false);
    TAILQ_FOREACH(thread, &channel->threads, entries) {
        if (thread && strcmp(thread->thread_data->uuid, thread_uuid) == 0) {
            return (true);
        }
    }
    return (false);
}
