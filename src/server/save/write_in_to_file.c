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

unsigned int write_global_struct(void)
{
    FILE *fd = NULL;

    fd = open_file("my_teams.db", "w");
    if (fd == NULL)
        return ERROR;
    write_users(fd);
    write_teams(fd);
    fclose(fd);
    return SUCCESS;
}
