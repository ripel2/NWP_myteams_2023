/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_user_to_team
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_user_to_team(const char *team_uuid, const char *user_uuid)
{
    user_t *user = get_user_from_struct(user_uuid);
    team_uuid_t *team_uuid_list = malloc(sizeof(team_uuid_t));

    if (user == NULL || get_team_from_struct(team_uuid) == NULL
    || team_uuid_list == NULL)
        return (84);

    TAILQ_INSERT_TAIL(&user->team_uuids, team_uuid_list, entries);
    global->dll->functions[SERVER_EVENT_USER_SUBSCRIBED]
    (team_uuid, user_uuid);
    return (0);
}
