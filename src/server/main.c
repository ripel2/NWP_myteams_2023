/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet server main function
*/

#include <stdio.h>
#include <string.h>
#include "shared.h"
#include "data.h"
#include "save.h"

global_t global = {0};

int main(int ac, char **av)
{
    FILE *fd = NULL;

    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    fd = open_file("data.bin", "w");
    if (fd == NULL)
        return 84;
    write_global(fd);
    return 0;
}
