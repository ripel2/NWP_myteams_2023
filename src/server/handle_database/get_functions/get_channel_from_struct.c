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


static channel_t *seek_in_teams(const char *uuid, team_t *team)
{
    channel_t *channel = NULL;

    TAILQ_FOREACH(channel, &team->channels, entries) {
        if (channel && strcmp(channel->channel_data->uuid, uuid) == 0) {
            return channel;
        }
    }
    return channel;
}

channel_t *get_channel_from_struct(const char *uuid)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    TAILQ_FOREACH(team, &global->teams, entries) {
        channel = seek_in_teams(uuid, team);
    }
    return channel;
}
