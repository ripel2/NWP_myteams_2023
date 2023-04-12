/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** data_struct_functions
*/

#pragma once
#include "loader.h"
#include "data.h"

int add_user_to_struct(const char *username, dlloader_t *dll, global_t *global);
user_t *get_user_from_struct(const char *uuid, global_t *global, dlloader_t *dll);

char *generate_uuid(char *uuid);
