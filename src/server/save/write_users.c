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

int count_users(void)
{
    user_t *user = NULL;
    int nb_users = 0;

    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        nb_users++;
    }
    return nb_users;
}

void write_users(FILE *fd)
{
    user_t *user = NULL;
    int nb_users = count_users();

    fwrite(&nb_users, sizeof(int), 1, fd);
    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        fwrite(user->user_data, sizeof(data_t), 1, fd);
        fwrite(&user->is_logged, sizeof(bool), 1, fd);
        write_team_uuids(fd, user);
    }
}
