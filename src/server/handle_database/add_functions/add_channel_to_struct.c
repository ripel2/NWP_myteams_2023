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
    team_t *new_team = malloc(sizeof(team_t));

    if (new_team == NULL)
        return (84);
    new_team->name[0] = '\0';
    new_team->uuid[0] = '\0';
    new_team->description[0] = '\0';
    strcat(new_team->name, name);
    strcat(new_team->uuid, uuid);
    strcat(new_team->description, description);
    global->dll->functions[CLIENT_PRINT_TEAM_CREATED]
    (new_team->uuid, new_team->name, new_team->description);
    TAILQ_INIT(&new_team->channels);
    TAILQ_INSERT_TAIL(&global->teams, new_team, entries);
    return (0);
}
