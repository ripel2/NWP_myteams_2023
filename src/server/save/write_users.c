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

static unsigned int count_users(void)
{
    user_t *user = NULL;
    unsigned int nb_users = 0;

    TAILQ_FOREACH(user, &global->users, entries) {
        nb_users++;
    }
    return nb_users;
}

void write_users(FILE *fd)
{
    user_t *user = NULL;
    unsigned int nb_users = count_users();

    fwrite(&nb_users, sizeof(unsigned int), 1, fd);
    TAILQ_FOREACH(user, &global->users, entries) {
        fwrite(user->user_data, sizeof(data_t), 1, fd);
        write_team_uuids(fd, user);
        write_personal_discussion(fd, user);
    }
}
