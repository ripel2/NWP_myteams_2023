/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_channel_to_struct
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>

int add_channel_to_struct(const char *team_uuid, data_t *channel_data)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    team_t *team_selected = get_team_from_struct(team_uuid);

    if (new_channel == NULL)
        return (ERROR);
    if (team_selected == NULL)
        return (ERROR);
    new_channel->channel_data = channel_data;
    TAILQ_INIT(&new_channel->threads);
    TAILQ_INSERT_TAIL(&team_selected->channels, new_channel, entries);
    return (SUCCESS);
}
