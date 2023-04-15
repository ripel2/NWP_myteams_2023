/*
** EPITECH PROJECT, 2023
** write_in_to_file
** File description:
** This file contains the write_in_to_file function
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "data.h"
#include "save.h"

void write_users(FILE *fd)
{
    user_t *user = NULL;
    int nb_users = 0;
    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        nb_users++;
    }
    fwrite(&nb_users, sizeof(int), 1, fd);
    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        fwrite(user->user_data, sizeof(data_t), 1, fd);
        fwrite(&user->is_logged, sizeof(bool), 1, fd);
    }
}

void read_users(FILE *fd)
{
    int nb_users = 0;
    if (fread(&nb_users, sizeof(int), 1, fd) == 0)
        return;
    for (int i = 0; i < nb_users; i++) {
        data_t *data = malloc(sizeof(data_t));
        fread(data, sizeof(data_t), 1, fd);
        printf("data->name: %s\t", data->name);
        printf("data->description: %s\t", data->description);
        printf("data->body: %s\t", data->body);
        printf("data->uuid: %s\n", data->uuid);
        bool is_logged = false;
        fread(&is_logged, sizeof(bool), 1, fd);
        printf("user->is_logged: %s\n", (is_logged == true) ? "Oui" : "Nope");
    }
    printf("nb_users: %d\n", nb_users);
}

unsigned int write_global(void)
{
    FILE *fd = NULL;

    fd = open_file("data.bin", "w");
    if (fd == NULL)
        return ERROR;
    write_users(fd);
    fclose(fd);
    fd = open_file("data.bin", "r");
    if (fd == NULL)
        return ERROR;
    read_users(fd);
    fclose(fd);
    return SUCCESS;
}
