/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** str_to_time
*/

#include "shared.h"

#include <string.h>
#include <stdio.h>

time_t client_get_time_from_string(char *time_str)
{
    time_t time = 0;

    sscanf(time_str, "%ld", &time);
    return time;
}
