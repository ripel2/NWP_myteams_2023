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

void read_threads(FILE *fd, channel_t *channel)
{
    unsigned int nb_threads = 0;
    thread_t *thread = NULL;

    fread(&nb_threads, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_threads; i++) {
        thread = malloc(sizeof(thread_t));
        thread->user_data = malloc(sizeof(data_t));
        thread->thread_data = malloc(sizeof(data_t));
        if (thread == NULL || thread->user_data == NULL ||
        thread->thread_data == NULL)
            return;
        fread(thread->user_data, sizeof(data_t), 1, fd);
        fread(thread->thread_data, sizeof(data_t), 1, fd);
        add_thread_to_struct(channel->channel_data->uuid,
        thread->user_data, thread->thread_data);
        read_replies(fd, thread);
    }
}
