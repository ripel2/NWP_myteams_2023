/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet client main function
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shared.h"
#include "data.h"
#include "client.h"


int main(int ac, char **av)
{
    client_t client = {0};

    if (print_help_if_needed(ac, av) == true)
        return (0);
    if (is_port_valid(av[2]) == false || is_ip_valid(av[1]) == false)
        return (84);
    printf("Connecting to %s:%s", av[1], av[2]);
    if (client_init(&client, av[1], atoi(av[2])) == errno)
        return (84);
    if 
    return 0;
}
