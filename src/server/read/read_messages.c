/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** load_struct_from_file
*/

#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "logging_server.h"
#include "data_struct_functions.h"

void read_messages(FILE *fd, personal_discussion_t *discussion)
{
    unsigned int nb_messages = 0;
    message_t *message = NULL;

    fread(&nb_messages, sizeof(unsigned int), 1, fd);
    TAILQ_INIT(&discussion->messages);
    for (unsigned int i = 0; i < nb_messages; i++) {
        message = calloc(1, sizeof(message_t));
        if (message == NULL)
            return;
        message->user_data = calloc(1, sizeof(data_t));
        message->message_data = calloc(1, sizeof(data_t));
        if (message->user_data == NULL || message->message_data == NULL)
            return;
        fread(message->user_data, sizeof(data_t), 1, fd);
        fread(message->message_data, sizeof(data_t), 1, fd);
        fread(&message->creation_date, sizeof(time_t), 1, fd);
        TAILQ_INSERT_TAIL(&discussion->messages, message, entries);
    }
}
