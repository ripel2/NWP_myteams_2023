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

void read_team_uuids(FILE *fd)
{
    unsigned int nb_team_uuids = 0;
    char *uuid = NULL;

    fread(&nb_team_uuids, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_team_uuids; i++) {
        uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        if (uuid == NULL)
            return;
        fread(uuid, sizeof(char) * UUID_LENGTH + 1, 1, fd);
        free(uuid);
    }
}

void read_users(FILE *fd)
{
    unsigned int nb_users = 0;
    user_t *user = NULL;

    fread(&nb_users, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_users; i++) {
        user = malloc(sizeof(user_t));
        user->user_data = malloc(sizeof(data_t));
        if (user == NULL || user->user_data == NULL)
            return;
        fread(user->user_data, sizeof(data_t), 1, fd);
        fread(&user->is_logged, sizeof(bool), 1, fd);
        add_user_to_struct(init_data(user->user_data->name,
            user->user_data->description, user->user_data->body,
            user->user_data->uuid));
        server_event_user_loaded(user->user_data->uuid, user->user_data->name);
        read_team_uuids(fd);
        read_personal_discussion(fd, user);
    }
}
