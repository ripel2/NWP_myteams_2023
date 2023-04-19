/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_thread_from_struct
*/

#include "data.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


static thread_t *seek_in_channels(const char *uuid, channel_t *channel)
{
    thread_t *thread = NULL;

    TAILQ_FOREACH(thread, &channel->threads, entries) {
        if (thread && strcmp(thread->thread_data->uuid, uuid) == 0) {
            return thread;
        }
    }
    return thread;
}

thread_t *get_thread_from_struct(const char *uuid)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            thread = seek_in_channels(uuid, channel);
        }
    }
    return thread;
}
