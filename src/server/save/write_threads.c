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

static unsigned int count_threads(channel_t *channel)
{
    thread_t *thread = NULL;
    unsigned int nb_threads = 0;

    TAILQ_FOREACH(thread, &channel->threads, entries) {
        nb_threads++;
    }
    return nb_threads;
}

void write_threads(FILE *fd, channel_t *channel)
{
    thread_t *thread = NULL;
    unsigned int nb_threads = count_threads(channel);

    fwrite(&nb_threads, sizeof(unsigned int), 1, fd);
    TAILQ_FOREACH(thread, &channel->threads, entries) {
        fwrite(thread->user_data, sizeof(data_t), 1, fd);
        fwrite(thread->thread_data, sizeof(data_t), 1, fd);
        fwrite(&thread->creation_date, sizeof(time_t), 1, fd);
        write_replies(fd, thread);
    }
}
