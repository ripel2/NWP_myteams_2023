/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** is_a_uuid
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

bool is_a_uuid(char *str)
{
    if (strlen(str) != 36)
        return false;
    if (str[8] != '-' || str[13] != '-'
    || str[18] != '-' || str[23] != '-')
        return false;
    return true;
}
