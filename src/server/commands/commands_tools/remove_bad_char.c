/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** remove_bad_char
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *remove_bad_char(char *str)
{
    if (str == NULL) {
        return str;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '\n' || str[i] == '\r')
            str[i] = '\0';
    }
    
    return str;
}
