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
#include "data_struct_functions.h"
#include "data.h"

global_t *global;

static dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

int main(int ac, char **av)
{
    global = malloc(sizeof(global_t));
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    global->dll = init_dll();
    add_team_to_struct("test", "00000000-0000-0000-0000-000000000000"
    , "poire");
    add_channel_to_struct("00000000-0000-0000-0000-000000000000", "test"
    , "00000000-0000-0000-0000-000000000001", "poire");
    get_channel_from_struct("00000000-0000-0000-0000-000000000001");
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    return 0;
}
