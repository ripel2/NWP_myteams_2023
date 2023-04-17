/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_discussion_from_struct
*/

#include "data.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


personal_discussion_t *get_personnal_discussion_from_struct(const char *uuid)
{
    user_t *user;
    personal_discussion_t *discussion;

    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            if (discussion && strcmp(discussion->uuid, uuid)
            == 0) {
                return discussion;
            }
        }
    }
    return discussion;
}
