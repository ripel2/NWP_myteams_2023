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


user_t *get_user_from_struct(const char *uuid)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && strcmp(user->user_data->uuid, uuid) == 0) {
            return user;
        }
    }
    return user;
}
