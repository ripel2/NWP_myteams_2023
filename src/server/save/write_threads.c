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

int count_threads(channel_t *channel)
{
    thread_t *thread = NULL;
    int nb_threads = 0;

    for (thread = TAILQ_FIRST(&channel->threads); thread != NULL;
        thread = TAILQ_NEXT(thread, entries)) {
        nb_threads++;
    }
    return nb_threads;
}

void write_threads(FILE *fd, channel_t *channel)
{
    thread_t *thread = NULL;
    int nb_threads = count_threads(channel);

    fwrite(&nb_threads, sizeof(int), 1, fd);
    for (thread = TAILQ_FIRST(&channel->threads); thread != NULL;
        thread = TAILQ_NEXT(thread, entries)) {
        fwrite(thread->user_data, sizeof(data_t), 1, fd);
        fwrite(thread->thread_data, sizeof(data_t), 1, fd);
        write_replies(fd, thread);
    }
}
