/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_user_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

/**
 * @brief add a user to the list of users in the data structure
 * @param username the username of the user
 * @param dll the dll loader containing all the functions of debug
*/
int add_user_to_struct(data_t *user_data)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (new_user == NULL)
        return (ERROR);
    new_user->is_logged = false;
    new_user->user_data = user_data;
    global->dll->functions[SERVER_EVENT_USER_CREATED]
    (new_user->user_data->uuid, new_user->user_data->name);
    TAILQ_INIT(&new_user->team_uuids);
    TAILQ_INIT(&new_user->discussions);
    TAILQ_INSERT_TAIL(&global->users, new_user, entries);
    return (SUCCESS);
}
