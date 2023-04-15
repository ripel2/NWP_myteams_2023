/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet server main function
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data.h"
#include "save.h"
#include "data_struct_functions.h"

global_t *global = {0};

static dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    if (dll == NULL)
        return NULL;
    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

int main(int ac, char **av)
{
    FILE *fd = NULL;

    global = malloc(sizeof(global_t));
    if (global == NULL)
        return ERROR;
    global->dll = init_dll();
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    fd = open_file("data.bin", "w");
    if (fd == NULL)
        return ERROR;
    write_global(fd);
    return SUCCESS;
}
