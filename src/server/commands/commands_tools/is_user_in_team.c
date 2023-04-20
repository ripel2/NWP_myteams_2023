/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_user_in_team
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

bool is_user_in_team(user_t *user, char *team_uuid)
{
    team_uuid_t *tmp_uuid_team = NULL;

    TAILQ_FOREACH(tmp_uuid_team, &user->team_uuids, entries) {
        if (tmp_uuid_team && strcmp(tmp_uuid_team->uuid, team_uuid) == 0) {
            return true;
        }
    }
    return false;
}