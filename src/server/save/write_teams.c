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

static unsigned int count_teams(void)
{
    team_t *team = NULL;
    unsigned int nb_teams = 0;

    TAILQ_FOREACH(team, &global->teams, entries) {
        nb_teams++;
    }
    return nb_teams;
}

void write_teams(FILE *fd)
{
    team_t *team = NULL;
    unsigned int nb_teams = count_teams();

    fwrite(&nb_teams, sizeof(unsigned int), 1, fd);
    TAILQ_FOREACH(team, &global->teams, entries) {
        fwrite(team->team_data, sizeof(data_t), 1, fd);
        write_channels(fd, team);
    }
}
