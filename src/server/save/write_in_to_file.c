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
#include "data_struct_functions.h"

void read_users(FILE *fd)
{
    int nb_users = 0;
    if (fread(&nb_users, sizeof(int), 1, fd) == 0)
        return;
    printf("nb_users: %d\n", nb_users);
    for (int i = 0; i < nb_users; i++) {
        data_t *data = malloc(sizeof(data_t));
        fread(data, sizeof(data_t), 1, fd);
        printf("data->name: %s\t", data->name);
        printf("data->description: %s\t", data->description);
        printf("data->body: %s\n", data->body);
        printf("data->uuid: %s\t", data->uuid);
        bool is_logged = false;
        fread(&is_logged, sizeof(bool), 1, fd);
        printf("user->is_logged: %s\n", (is_logged == true) ? "Oui" : "Nope");
        int nb_team_uuids = 0;
        fread(&nb_team_uuids, sizeof(int), 1, fd);
        printf("nb_team_uuids: %d\t", nb_team_uuids);
        for (int j = 0; j < nb_team_uuids; j++) {
            char *uuid = malloc(sizeof(char) * (UUID_LENGTH + 1));
            fread(uuid, sizeof(char), (UUID_LENGTH + 1), fd);
            printf("uuid: %s\n", uuid);
        }
        int nb_personal_discussions = 0;
        fread(&nb_personal_discussions, sizeof(int), 1, fd);
        printf("nb_personal_discussions: %d\t", nb_personal_discussions);
        for (int j = 0; j < nb_personal_discussions; j++) {
            data_t *data2 = malloc(sizeof(data_t));
            char *uuid = malloc(sizeof(char) * (UUID_LENGTH + 1));
            fread(data2, sizeof(data_t), 1, fd);
            printf("data2->name: %s\n\n", data2->name);
            printf("data2->description: %s\n", data2->description);
            printf("data2->body: %s\n", data2->body);
            printf("data2->uuid: %s\n\n", data2->uuid);
            fread(uuid, sizeof(char), (UUID_LENGTH + 1), fd);
            printf("uuid: %s\n", uuid);
            free(uuid);
            int nb_messages = 0;
            fread(&nb_messages, sizeof(int), 1, fd);
            printf("nb_messages: %d\n", nb_messages);
            for (int k = 0; k < nb_messages; k++) {
                data_t *data3 = malloc(sizeof(data_t));
                fread(data3, sizeof(data_t), 1, fd);
                printf("data3->name: %s\t", data3->name);
                printf("data3->description: %s\t", data3->description);
                printf("data3->body: %s\t", data3->body);
                data_t *data4 = malloc(sizeof(data_t));
                fread(data4, sizeof(data_t), 1, fd);
                printf("data3->name: %s\t", data3->name);
                printf("data3->description: %s\t", data3->description);
                printf("data3->body: %s", data3->body);
            }
        }
    }
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
