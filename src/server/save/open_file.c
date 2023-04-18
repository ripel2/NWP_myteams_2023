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
        write(1, "Error: path or mode is NULL", 27);
        return NULL;
    }
    if (access(path, F_OK) == -1) {
        fd = fopen(path, "w");
        if (fd == NULL) {
            write(1, "Error: can't create the file", 28);
            return NULL;
        }
        fclose(fd);
    }
    fd = fopen(path, mode);
    if (fd == NULL) {
        write(1, "Error: can't open the file", 26);
        return NULL;
    }
    return fd;
}
