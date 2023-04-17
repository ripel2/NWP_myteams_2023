/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_channel_to_struct
*/

#include "data.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


static reply_t *seek_in_threads(const char *uuid, thread_t *thread)
{
    reply_t *reply;

    TAILQ_FOREACH(reply, &thread->replies, entries) {
        if (reply && strcmp(reply->reply_data->uuid, uuid) == 0) {
            return reply;
        }
    }
    return reply;
}

static reply_t *seek_in_channels(const char *uuid, channel_t *channel)
{
    reply_t *reply;
    thread_t *thread;

    TAILQ_FOREACH(thread, &channel->threads, entries) {
        reply = seek_in_threads(uuid, thread);
    }
    return reply;
}

reply_t *get_reply_from_struct(const char *uuid)
{
    team_t *team;
    channel_t *channel;
    reply_t *reply;

    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            reply = seek_in_channels(uuid, channel);
        }
    }
    return reply;
}
