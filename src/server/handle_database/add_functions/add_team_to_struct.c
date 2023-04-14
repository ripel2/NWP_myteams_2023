/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_team_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_team_to_struct(data_t *team_data)
{
    team_t *new_team = malloc(sizeof(team_t));

    if (new_team == NULL)
        return (84);
    new_team->team_data = team_data;
    global->dll->functions[CLIENT_PRINT_TEAM_CREATED]
    (new_team->team_data->uuid, new_team->team_data->name, new_team->team_data->description);
    TAILQ_INIT(&new_team->channels);
    TAILQ_INSERT_TAIL(&global->teams, new_team, entries);
    return (0);
}
