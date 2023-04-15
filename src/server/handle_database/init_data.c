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
    data_t *data = malloc(sizeof(data_t));

    if (data == NULL)
        return NULL;
    data->name[0] = '\0';
    data->description[0] = '\0';
    data->uuid[0] = '\0';
    data->body[0] = '\0';
    strcat(data->name, name);
    strcat(data->description, description);
    strcat(data->uuid, uuid);
    strcat(data->body, body);
    return data;
}
