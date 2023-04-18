/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_channel_in_team
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>

bool is_channel_in_team(const char *channel_uuid, const char *team_uuid)
{
    team_t *team = get_team_from_struct(team_uuid);
    channel_t *channel = NULL;

    if (team == NULL || get_channel_from_struct(channel_uuid) == NULL)
        return (false);
    TAILQ_FOREACH(channel, &team->channels, entries) {
        if (channel && strcmp(channel->channel_data->uuid, channel_uuid) == 0) {
            return (true);
        }
    }
    return (false);
}
