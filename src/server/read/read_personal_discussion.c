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
    unsigned int nb_personal_discussion = 0;
    data_t *user_data = NULL;
    char *uuid = NULL;
    char *discussion_uuid = NULL;

    fread(&nb_personal_discussion, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_personal_discussion; i++) {
        user_data = malloc(sizeof(data_t));
        fread(user_data, sizeof(data_t), 1, fd);
        uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        fread(uuid, sizeof(char) * UUID_LENGTH + 1, 1, fd);
        discussion_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        generate_uuid(discussion_uuid);
        add_personnal_discussion_to_struct(discussion_uuid,
        owner->user_data->uuid, user_data);
        read_messages(fd, owner);
    }
}
