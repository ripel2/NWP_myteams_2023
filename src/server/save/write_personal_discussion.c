/*
** EPITECH PROJECT, 2023
** write_teams_uuids
** File description:
** This file contains the write_teams_uuids function
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "data.h"
#include "save.h"


int count_messages(personal_discussion_t *personal_discussion)
{
    message_t *message = NULL;
    int nb_messages = 0;

    for (message = TAILQ_FIRST(&personal_discussion->messages);
        message != NULL;
        message = TAILQ_NEXT(message, entries)) {
        nb_messages++;
    }
    return nb_messages;
}

void write_messages(FILE *fd, personal_discussion_t *personal_discussion)
{
    message_t *message = NULL;
    int nb_messages = count_messages(personal_discussion);

    fwrite(&nb_messages, sizeof(int), 1, fd);
    for (message = TAILQ_FIRST(&personal_discussion->messages);
        message != NULL;
        message = TAILQ_NEXT(message, entries)) {
        fwrite(message->user_data, sizeof(data_t), 1, fd);
        fwrite(message->message_data, sizeof(data_t), 1, fd);
    }
}

int count_personal_discussion(user_t *user)
{
    personal_discussion_t *personal_discussion = NULL;
    int nb_personal_discussion = 0;

    TAILQ_FOREACH(personal_discussion, &user->discussions, entries) {
        nb_personal_discussion++;
    }
    return nb_personal_discussion;
}

void write_personal_discussion(FILE *fd, user_t *user)
{
    personal_discussion_t *personal_discussion = NULL;
    int nb_personal_discussion = count_personal_discussion(user);

    fwrite(&nb_personal_discussion, sizeof(int), 1, fd);
    TAILQ_FOREACH(personal_discussion, &user->discussions, entries) {
        fwrite(personal_discussion->user_data, sizeof(data_t), 1, fd);
        fwrite(&personal_discussion->uuid, sizeof(char), (UUID_LENGTH + 1), fd);
        write_messages(fd, personal_discussion);
    }
}
