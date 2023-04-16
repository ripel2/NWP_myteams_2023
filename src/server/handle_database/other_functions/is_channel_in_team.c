/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_channel_in_team
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int is_channel_in_team(const char *channel_uuid, const char *team_uuid)
{
    team_t *team = get_team_from_struct(team_uuid);
    channel_t *channel;

    if (team == NULL || get_channel_from_struct(channel_uuid) == NULL)
        return (84);
    TAILQ_FOREACH(channel, &team->channels, entries) {
        if (channel && strcmp(channel->channel_data->uuid, channel_uuid) == 0) {
            return (0);
        }
    }
    return (84);
}