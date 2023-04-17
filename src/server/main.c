/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"

global_t *global;

int main(int ac, char **av)
{
    global = malloc(sizeof(global_t));

    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    return SUCCESS;
}
