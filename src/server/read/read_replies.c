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

void read_replies(FILE *fd, thread_t *thread)
{
    unsigned int nb_replies = 0;
    reply_t *reply = NULL;

    fread(&nb_replies, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_replies; i++) {
        reply = malloc(sizeof(reply_t));
        reply->user_data = malloc(sizeof(data_t));
        reply->reply_data = malloc(sizeof(data_t));
        fread(reply->user_data, sizeof(data_t), 1, fd);
        fread(reply->reply_data, sizeof(data_t), 1, fd);
        add_reply_to_struct(thread->thread_data->uuid,
        reply->user_data, reply->reply_data);
    }
}
