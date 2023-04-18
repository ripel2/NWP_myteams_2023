/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** fixed_array_split
*/

#include "shared.h"
#include <stddef.h>
#include <string.h>

bool is_delimiter(char c, const char *delim)
{
    for (size_t i = 0; delim[i] != '\0'; i++)
        if (c == delim[i])
            return true;
    return false;
}

void split_string_fixed_array(char *str, char **args, size_t size)
{
    size_t token_idx = 0;
    bool in_quotes = false;
    char *arg_start = NULL;

    while (*str != '\0' && token_idx < size - 1) {
        if (*str == '"') {
            in_quotes = !in_quotes;
            arg_start = arg_start == NULL ? str : arg_start;
        } else if (is_delimiter(*str, " ") && !in_quotes && arg_start) {
            *str = '\0';
            args[token_idx++] = arg_start;
            arg_start = NULL;
        } else {
            arg_start = arg_start == NULL ? str : arg_start;
        }
        str++;
    }
    if (arg_start != NULL)
        args[token_idx++] = arg_start;
    args[token_idx] = NULL;
}
