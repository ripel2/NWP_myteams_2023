/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** init_data
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"

data_t *init_data(char *name, char *description, char *body, char *uuid)
{
    data_t *data = calloc(1, sizeof(data_t));

    if (data == NULL)
        return NULL;
    strcpy(data->name, name);
    strcpy(data->description, description);
    strcpy(data->uuid, uuid);
    strcpy(data->body, body);
    return data;
}
