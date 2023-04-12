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
#include "loader.h"

team_t *get_team_from_struct(const char *uuid, global_t *global)
{
    team_t *team;

    TAILQ_FOREACH(team, &global->teams, entries) {
        if (team && strcmp(team->uuid, uuid) == 0) {
            global->dll->functions[CLIENT_PRINT_TEAM](team->uuid, team->name, team->description);
            return team;
        }
    }
    global->dll->functions[CLIENT_ERROR_UNKNOWN_TEAM](uuid);
    return team;
}
