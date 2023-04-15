/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023
** File description:
** store_struct_in_file
*/

#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

global_t global = {0};

int write_user_list(FILE *file)
{
    user_t *user = NULL;

    fwrite(TAILQ_COUNT(&global.users), sizeof(int), 1, file);
    TAILQ_FOREACH(user, &global.users, entries) {
        fwrite(user, sizeof(user_t), 1, file);
    }
    return 0;
}

int store_struct_in_file(void)
{
    FILE *file = fopen("teams.db", "w");
    int ret = 0;

    if (file == NULL)
        return errno;
    ret = write_user_list(file);
    if (ret != 0)
        return ret;
    ret = write_message_list(file);
    if (ret != 0)
        return ret;
    ret = write_team_list(file);
    if (ret != 0)
        return ret;
    return 0;
}
