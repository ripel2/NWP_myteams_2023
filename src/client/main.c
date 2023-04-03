/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet client main function
*/

#include <stdio.h>
#include <string.h>
#include "shared.h"
#include "data.h"

global_t global = {0};

int main(int ac, char **av)
{
    print_help_if_needed(ac, av);
    is_port_valid(av[2]);
    return 0;
}
