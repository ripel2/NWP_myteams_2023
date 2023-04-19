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

static unsigned int count_channels(team_t *team)
{
    channel_t *channel = NULL;
    unsigned int nb_channels = 0;

    TAILQ_FOREACH(channel, &team->channels, entries) {
        nb_channels++;
    }
    return nb_channels;
}

void write_channels(FILE *fd, team_t *team)
{
    channel_t *channel = NULL;
    unsigned int nb_channels = count_channels(team);

    fwrite(&nb_channels, sizeof(unsigned int), 1, fd);
    TAILQ_FOREACH(channel, &team->channels, entries) {
        fwrite(channel->channel_data, sizeof(data_t), 1, fd);
        write_threads(fd, channel);
    }
}
