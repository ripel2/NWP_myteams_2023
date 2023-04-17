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

    for (team_uuids = TAILQ_FIRST(&user->team_uuids); team_uuids != NULL;
        team_uuids = TAILQ_NEXT(team_uuids, entries)) {
        nb_teams++;
    }
    return nb_teams;
}

void write_team_uuids(FILE *fd, user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    int nb_team_uuids = count_team_uuids(user);

    fwrite(&nb_team_uuids, sizeof(int), 1, fd);
    for (team_uuid = TAILQ_FIRST(&user->team_uuids); team_uuid != NULL;
        team_uuid = TAILQ_NEXT(team_uuid, entries)) {
        fwrite(team_uuid->uuid, sizeof(char), (UUID_LENGTH + 1), fd);
    }
}
