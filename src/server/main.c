/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet server main function
*/

#include <stdio.h>
#include <string.h>
#include "shared.h"
#include "loader.h"
#include <unistd.h>

dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

void fini_dll(dlloader_t *dll)
{
    dlclose(dll->handle);
    free(dll);
}

int main(int ac, char **av)
{
    dlloader_t *dll = init_dll();

    (void)(av);
    (void)(ac);

    dll->functions[CLIENT_CHANNEL_PRINT_THREADS]("a", "a", 1, "a", "a");

    fini_dll(dll);
    return 0;
}
