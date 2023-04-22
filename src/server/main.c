/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"
#include "server.h"
#include "teams_server.h"
#include "save.h"

global_t *global;

void sigint_handler(int sig)
{
    (void)sig;
    write_global_struct();
    exit(0);
}

int main(int ac, char **av)
{
    server_t server = {0};

    global = malloc(sizeof(global_t));
    if (!global)
        return ERROR;
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    if (print_help_if_needed(ac, av) == true)
        return SUCCESS;
    if (!is_port_valid(av[1]))
        return ERROR;
    if (server_init(&server, atoi(av[1])) != 0)
        return ERROR;
    if (load_global_struct() == ERROR)
        return ERROR;
    signal(SIGINT, sigint_handler);
    teams_server_loop(&server);
    return SUCCESS;
}
