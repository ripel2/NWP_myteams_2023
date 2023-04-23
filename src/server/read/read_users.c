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

void read_team_uuids(FILE *fd, user_t *user)
{
    unsigned int nb_team_uuids = 0;
    team_uuid_t *uuid = NULL;

    fread(&nb_team_uuids, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_team_uuids; i++) {
        uuid = malloc(sizeof(team_uuid_t));
        if (uuid == NULL)
            return;
        fread(uuid->uuid, sizeof(char) * UUID_LENGTH + 1, 1, fd);
        TAILQ_INSERT_TAIL(&user->team_uuids, uuid, entries);
    }
}

void read_users(FILE *fd)
{
    unsigned int nb_users = 0;
    user_t *user = NULL;

    fread(&nb_users, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_users; i++) {
        user = calloc(1, sizeof(user_t));
        if (user == NULL)
            return;
        user->user_data = calloc(1, sizeof(data_t));
        if (user->user_data == NULL)
            return;
        fread(user->user_data, sizeof(data_t), 1, fd);
        read_team_uuids(fd, user);
        read_personal_discussion(fd, user);
        TAILQ_INSERT_TAIL(&global->users, user, entries);
        server_event_user_loaded(user->user_data->uuid, user->user_data->name);
    }
}
