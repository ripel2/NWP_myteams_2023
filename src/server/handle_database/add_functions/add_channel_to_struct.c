/*
** EPITECH PROJECT, 2023
** $
** File description:
** add_channel_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_channel_to_struct(const char *team_uuid, const char *name, const char *uuid,
const char *description)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    team_t *team_selected = get_team_from_struct(team_uuid);

    if (new_channel == NULL)
        return (84);
    if (team_selected == NULL)
        global->dll->functions[CLIENT_ERROR_UNKNOWN_TEAM](team_uuid);
    new_channel->name[0] = '\0';
    new_channel->uuid[0] = '\0';
    new_channel->description[0] = '\0';
    strcat(new_channel->name, name);
    strcat(new_channel->uuid, uuid);
    strcat(new_channel->description, description);
    TAILQ_INIT(&new_channel->threads);
    TAILQ_INSERT_TAIL(&team_selected->channels, new_channel, entries);
    global->dll->functions[CLIENT_PRINT_CHANNEL_CREATED](new_channel->uuid, new_channel->name, new_channel->description);
    return (0);
}