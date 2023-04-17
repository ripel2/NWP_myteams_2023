/*
** EPITECH PROJECT, 2023
** shared
** File description:
** In this file for the shared
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <time.h>

bool print_help_if_needed(int ac, char **av);
bool is_port_valid(const char *port);
bool is_ip_valid(const char *ip);

void split_string_fixed_array(char *command, char **args, size_t size);
time_t client_get_time_from_string(char *time_str);
