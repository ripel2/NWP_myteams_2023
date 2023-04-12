/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** generate_uuid
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

char *generate_uuid(char *uuid)
{
    char charset[] = "0123456789abcdef";

    for (int i = 0; i < UUID_LENGTH; i++) {
        uuid[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    uuid[UUID_LENGTH] = '\0';
    uuid[8] = '-';
    uuid[13] = '-';
    uuid[18] = '-';
    uuid[23] = '-';
    return (uuid);
}
