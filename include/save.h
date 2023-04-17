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
