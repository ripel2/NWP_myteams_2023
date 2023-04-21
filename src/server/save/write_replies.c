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

static unsigned int count_replies(thread_t *thread)
{
    reply_t *reply = NULL;
    unsigned int nb_replies = 0;

    TAILQ_FOREACH(reply, &thread->replies, entries) {
        nb_replies++;
    }
    return nb_replies;
}

void write_replies(FILE *fd, thread_t *thread)
{
    reply_t *reply = NULL;
    unsigned int nb_replies = count_replies(thread);

    fwrite(&nb_replies, sizeof(unsigned int), 1, fd);
    TAILQ_FOREACH(reply, &thread->replies, entries) {
        fwrite(reply->user_data, sizeof(data_t), 1, fd);
        fwrite(reply->reply_data, sizeof(data_t), 1, fd);
        fwrite(&reply->creation_date, sizeof(time_t), 1, fd);
    }
}
