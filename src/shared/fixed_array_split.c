/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** fixed_array_strip
*/

#include "shared.h"

#include <string.h>

void string_strip_delim_start(char **str, char delim)
{
    while (**str == delim)
        (*str)++;
}

void string_strip_delim_end(char **str, char delim)
{
    int len = strlen(*str);

    while (len > 0 && (*str)[len - 1] == delim)
        len--;
    (*str)[len] = '\0';
}

void string_strip_delim(char **str, char delim)
{
    string_strip_delim_start(str, delim);
    string_strip_delim_end(str, delim);
}

static void split_string_inner(char *str, char **args, size_t size)
{
    size_t token_idx = 0;
    bool in_quotes = false;
    char *arg_start = NULL;

    while (*str != '\0' && token_idx < size - 1) {
        if (*str == '"') {
            in_quotes = !in_quotes;
            arg_start = arg_start == NULL ? str : arg_start;
        }
        if (*str == ' ' && !in_quotes && arg_start) {
            *str = '\0';
            args[token_idx++] = arg_start;
            arg_start = NULL;
        } else
            arg_start = arg_start == NULL ? str : arg_start;
        str++;
    }
    if (arg_start != NULL)
        args[token_idx++] = arg_start;
    args[token_idx] = NULL;
}

void split_string_fixed_array(char *str, char **args, size_t size)
{
    char *cpy = str;

    string_strip_delim_end(&cpy, ' ');
    string_strip_delim_start(&cpy, ' ');
    split_string_inner(cpy, args, size);
}
