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
int add_user_to_struct(const char *username, const char *uuid, global_t *global)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (new_user == NULL)
        return (84);
    new_user->username[0] = '\0';
    new_user->uuid[0] = '\0';
    strcat(new_user->username, username);
    strcat(new_user->uuid, uuid);
    new_user->is_logged = false;
    global->dll->functions[CLIENT_PRINT_USER](new_user->uuid,
    new_user->username, new_user->is_logged);
    TAILQ_INIT(&new_user->team_uuids);
    TAILQ_INIT(&new_user->discussions);
    TAILQ_INSERT_TAIL(&global->users, new_user, entries);
    return (0);
}
