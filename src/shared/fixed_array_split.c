/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** fixed_array_split
*/

#include "shared.h"

#include <string.h>

void split_string_fixed_array(char *command, char **args, size_t size)
{
    char *token = strtok(command, " ");
    size_t c = 0;

    for (c = 0; c < size - 1; c++) {
        if (token == NULL)
            break;
        args[c] = token;
        token = strtok(NULL, " ");
    }
    args[c] = NULL;
}
