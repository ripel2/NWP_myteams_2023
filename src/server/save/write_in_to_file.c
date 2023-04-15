/*
** EPITECH PROJECT, 2023
** write_in_to_file
** File description:
** In this file for the write_in_to_file function
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "data.h"

void write_global(FILE *fp)
{
    (void)fp;
    user_t *user;
    TAILQ_FOREACH(user, &global->users, entries) {
        // write_user_data(fp, user);
    }
}

