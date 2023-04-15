/*
** EPITECH PROJECT, 2023
** open_file
** File description:
** In this file for the open_file function
*/

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);

    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}
