/*
** EPITECH PROJECT, 2023
** open_file
** File description:
** In this file for the open_file function
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *open_file(const char *path, const char *mode)
{
    FILE *fd = NULL;

    if (path == NULL || mode == NULL) {
        perror("Error the path or the mode is NULL");
        return NULL;
    }
    if (access(path, F_OK) == -1) {
        fd = fopen(path, "w");
        if (fd == NULL) {
            perror("Error creating the file");
            return NULL;
        }
        fclose(fd);
    }
    fd = fopen(path, mode);
    if (fd == NULL) {
        perror("Error opening file");
        return NULL;
    }
    return fd;
}
