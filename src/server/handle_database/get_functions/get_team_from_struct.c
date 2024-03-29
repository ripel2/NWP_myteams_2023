/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_team_from_struct
*/

#include "data.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


team_t *get_team_from_struct(const char *uuid)
{
    team_t *team = NULL;

    TAILQ_FOREACH(team, &global->teams, entries) {
        if (team && strcmp(team->team_data->uuid, uuid) == 0) {
            return team;
        }
    }
    return team;
}
