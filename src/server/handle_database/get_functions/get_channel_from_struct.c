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
#include "loader.h"

channel_t *get_channel_from_struct(const char *uuid)
{
    team_t *team;
    channel_t *channel;

    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            if (channel && strcmp(channel->channel_data->uuid, uuid) == 0) {
                global->dll->functions[CLIENT_PRINT_CHANNEL](channel->channel_data->uuid,
                channel->channel_data->name, channel->channel_data->description);
                return channel;
            }
        }
    }
    global->dll->functions[CLIENT_ERROR_UNKNOWN_CHANNEL](uuid);
    return channel;
}
