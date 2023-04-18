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

int count_team_uuids(user_t *user)
{
    team_uuid_t *team_uuids = NULL;
    int nb_teams = 0;

    TAILQ_FOREACH(team_uuids, &user->team_uuids, entries) {
        nb_teams++;
    }
    return nb_teams;
}

void write_team_uuids(FILE *fd, user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    int nb_team_uuids = count_team_uuids(user);

    fwrite(&nb_team_uuids, sizeof(int), 1, fd);
    TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
        fwrite(team_uuid->uuid, sizeof(char), (UUID_LENGTH + 1), fd);
    }
}
