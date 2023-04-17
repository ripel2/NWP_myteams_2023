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

void debug_init_data(void)
{
    // team_t *team;
    data_t *team_data1;
    data_t *team_data2;
    data_t *team_data3;
    char *uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data1 = init_data("Lucas", "Description", "", uuid[0]);
    team_data2 = init_data("Louis", "Description", "", uuid[1]);
    team_data3 = init_data("Andréas", "Description", "", uuid[2]);
    add_team_to_struct(team_data1);
    add_team_to_struct(team_data2);
    add_team_to_struct(team_data3);
}

int main(int ac, char **av)
{
    global = malloc(sizeof(global_t));
    if (global == NULL)
        return ERROR;
    global->dll = init_dll();
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    if (global->dll == NULL)
        return ERROR;
    if (print_help_if_needed(ac, av) == false && is_port_valid(av[1]) == false)
        return ERROR;
    debug_init_data();
    printf("WROOOOOO\n");
    write_global();
    return SUCCESS;
}