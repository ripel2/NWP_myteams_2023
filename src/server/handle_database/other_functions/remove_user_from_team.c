/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** remove_user_from_team
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>

int remove_user_from_team(const char *team_uuid, const char *user_uuid)
{
    user_t *user = get_user_from_struct(user_uuid);
    team_uuid_t *team_uuid_list;

    if (user == NULL || get_team_from_struct(team_uuid) == NULL)
        return (84);
    TAILQ_FOREACH(team_uuid_list, &user->team_uuids, entries) {
        if (team_uuid_list && strcmp(team_uuid_list->uuid, team_uuid) == 0) {
            TAILQ_REMOVE(&user->team_uuids, team_uuid_list, entries);
            free(team_uuid_list);
            return (0);
        }
    }
    return (84);
}
