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

unsigned int load_global_struct(void)
{
    FILE *fd = NULL;

    fd = open_file("my_teams.db", "r");
    if (fd == NULL)
        return ERROR;
    read_users(fd);
    read_teams(fd);
    fclose(fd);
    return SUCCESS;
}
