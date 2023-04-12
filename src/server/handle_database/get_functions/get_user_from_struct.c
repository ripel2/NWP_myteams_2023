/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_user_from_struct
*/

#include "data.h"

user_t *get_user_from_struct(const char *uuid, global_t *global)
{
    user_t *user;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && user->uuid == uuid) {
            return user;
        }
    }
    return user;
}
