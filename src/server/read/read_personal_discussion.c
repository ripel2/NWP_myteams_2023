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

void read_personal_discussion(FILE *fd, user_t *owner)
{
    personal_discussion_t *personal_discussion = NULL;
    unsigned int nb_personal_discussion = 0;

    fread(&nb_personal_discussion, sizeof(unsigned int), 1, fd);
    TAILQ_INIT(&owner->discussions);
    for (unsigned int i = 0; i < nb_personal_discussion; i++) {
        personal_discussion = calloc(1, sizeof(personal_discussion_t));
        if (personal_discussion == NULL)
            return;
        personal_discussion->user_data = calloc(1, sizeof(data_t));
        if (personal_discussion->user_data == NULL)
            return;
        fread(personal_discussion->user_data, sizeof(data_t), 1, fd);
        fread(personal_discussion->uuid, sizeof(char), UUID_LENGTH + 1, fd);
        read_messages(fd, personal_discussion);
        TAILQ_INSERT_TAIL(&owner->discussions, personal_discussion, entries);
    }
}
