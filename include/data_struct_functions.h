/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** data_struct_functions
*/

#pragma once
#include "loader.h"
#include "data.h"

int add_user_to_struct(const char *username, const char *uuid);
user_t *get_user_from_struct(const char *uuid);
int add_team_to_struct(const char *name, const char *uuid,
const char *description);
team_t *get_team_from_struct(const char *uuid);

char *generate_uuid(char *uuid);
