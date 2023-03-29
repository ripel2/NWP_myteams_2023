/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL : Ubuntu]
** File description:
** main
*/

#include "load_teams_library.h"

int main(int argc, char **argv)
{
    DLLoader_t *dll = malloc(sizeof(DLLoader_t));

    load_teams_library(argv[1], dll);
    
    dll->functions[CLIENT_EVENT_LOGGED_IN]("123e4567-e89b-12d3-a456-426614174000", "123e4567-e89b-12d3-a456-426614174000");
    dlclose(&dll->handle);
    free(dll);
}