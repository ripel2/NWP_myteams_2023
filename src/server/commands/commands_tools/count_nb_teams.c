/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** count_nb_teams
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

int count_nb_teams(user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    int nb_teams = 0;

    TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
        nb_teams++;
    }
    return nb_teams;
}
