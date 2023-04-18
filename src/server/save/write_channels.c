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

int count_channels(team_t *team)
{
    channel_t *channel = NULL;
    int nb_channels = 0;

    for (channel = TAILQ_FIRST(&team->channels); channel != NULL;
        channel = TAILQ_NEXT(channel, entries)) {
        nb_channels++;
    }
    return nb_channels;
}

void write_channels(FILE *fd, team_t *team)
{
    channel_t *channel = NULL;
    int nb_channels = count_channels(team);

    fwrite(&nb_channels, sizeof(int), 1, fd);
    for (channel = TAILQ_FIRST(&team->channels); channel != NULL;
        channel = TAILQ_NEXT(channel, entries)) {
        fwrite(channel->channel_data, sizeof(data_t), 1, fd);
        write_threads(fd, channel);
    }
}
