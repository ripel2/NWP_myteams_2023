/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** count_nb_messages
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

static personal_discussion_t *get_discussion_between_user
(user_t *current_user, user_t *user_to_seek)
{
    personal_discussion_t *discussion = NULL;

    TAILQ_FOREACH(discussion, &current_user->discussions, entries) {
        if (discussion->user_data->uuid == user_to_seek->user_data->uuid) {
            return discussion;
        }
    }
    return NULL;
}

int count_nb_messages(user_t *current_user, user_t *user_to_seek)
{
    personal_discussion_t *discussion =
    get_discussion_between_user(current_user, user_to_seek);
    int nb_messages = 0;
    message_t *message = NULL;

    TAILQ_FOREACH(message, &discussion->messages, entries) {
        nb_messages++;
    }
    return nb_messages;
}
