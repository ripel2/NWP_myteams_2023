/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** generate_uuid
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

char *generate_uuid(char *uuid)
{
    uuid_t uuidst = {0};

    uuid_generate(uuidst);
    uuid_unparse(uuidst, uuid);
    return uuid;
}
