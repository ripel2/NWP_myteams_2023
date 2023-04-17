/*
** EPITECH PROJECT, 2023
** save
** File description:
** In this file for the save function
*/

#pragma once

#include <stdio.h>
#include "data.h"
#include "loader.h"

FILE *open_file(const char *path, const char *mode);
unsigned int write_global(void);
void write_users(FILE *fd);
int count_team_uuids(user_t *user);
void write_team_uuids(FILE *fd, user_t *user);
