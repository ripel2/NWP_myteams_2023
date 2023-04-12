/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_user_from_struct
*/

#include "data.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "loader.h"

user_t *get_user_from_struct(const char *uuid, global_t *global, dlloader_t *dll)
{
    user_t *user;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && strcmp(user->uuid, uuid) == 0) {       
            dll->functions[CLIENT_PRINT_USER](user->uuid,
            user->username, user->is_logged);
            return user;
        }
    }
    dll->functions[CLIENT_ERROR_UNKNOWN_USER](uuid);
    return user;
}
