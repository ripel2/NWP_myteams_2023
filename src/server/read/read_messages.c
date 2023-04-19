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

void read_messages(FILE *fd, user_t *user)
{
    unsigned int nb_messages = 0;
    message_t *message = NULL;

    fread(&nb_messages, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_messages; i++) {
        message = malloc(sizeof(message_t));
        message->user_data = malloc(sizeof(data_t));
        message->message_data = malloc(sizeof(data_t));
        fread(message->user_data, sizeof(data_t), 1, fd);
        fread(message->message_data, sizeof(data_t), 1, fd);
        add_message_to_struct(user->user_data,
        message->user_data, message->message_data);
    }
}
