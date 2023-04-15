/*
** EPITECH PROJECT, 2023
** myteams_cli
** File description:
** myteams_cli main function
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "shared.h"
#include "data.h"
#include "client.h"
#include "client_functions.h"

int main(int ac, char **av)
{
    client_t client = {0};
    int ret = 0;

    if (print_help_if_needed(ac, av) == true)
        return (0);
    if (is_port_valid(av[2]) == false || is_ip_valid(av[1]) == false)
        return (84);
    ret = client_init(&client, av[1], atoi(av[2]));
    if (ret != 0)
        return (84);
    return teams_client_loop(&client);
}
