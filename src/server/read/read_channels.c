/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** load_struct_from_file
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "data.h"
#include "save.h"
#include "data_struct_functions.h"

void read_channels(FILE *fd, team_t *team)
{
    unsigned int nb_channels = 0;
    channel_t *channel = NULL;

    fread(&nb_channels, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_channels; i++) {
        channel = malloc(sizeof(channel_t));
        if (channel == NULL)
            return;
        channel->channel_data = malloc(sizeof(data_t));
        if (channel->channel_data == NULL)
            return;
        fread(channel->channel_data, sizeof(data_t), 1, fd);
        add_channel_to_struct(team->team_data->uuid, channel->channel_data);
        read_threads(fd, channel);
    }
}
