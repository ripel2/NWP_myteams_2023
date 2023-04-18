/*
** EPITECH PROJECT, 2023
** write_in_to_file
** File description:
** This file contains the write_in_to_file function
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "data.h"
#include "save.h"
#include "data_struct_functions.h"

int count_teams(void)
{
    team_t *team = NULL;
    int nb_teams = 0;

    for (team = TAILQ_FIRST(&global->teams); team != NULL;
        team = TAILQ_NEXT(team, entries)) {
        nb_teams++;
    }
    return nb_teams;
}

void write_teams(FILE *fd)
{
    team_t *team = NULL;
    int nb_teams = count_teams();

    fwrite(&nb_teams, sizeof(int), 1, fd);
    for (team = TAILQ_FIRST(&global->teams); team != NULL;
        team = TAILQ_NEXT(team, entries)) {
        fwrite(team->team_data, sizeof(data_t), 1, fd);
        write_channels(fd, team);
    }
}
