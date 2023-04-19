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

void read_teams(FILE *fd)
{
    unsigned int nb_teams = 0;
    team_t *team = NULL;

    fread(&nb_teams, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_teams; i++) {
        team = malloc(sizeof(team_t));
        team->team_data = malloc(sizeof(data_t));
        fread(team->team_data, sizeof(data_t), 1, fd);
        add_team_to_struct(team->team_data);
        read_channels(fd, team);
    }
}
