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


int count_users(void)
{
    user_t *user = NULL;
    int nb_users = 0;

    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        nb_users++;
    }
    return nb_users;
}

int count_team_uuids(user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    int nb_team_uuids = 0;

    for (team_uuid = TAILQ_FIRST(&user->team_uuids); team_uuid != NULL;
        team_uuid = TAILQ_NEXT(team_uuid, entries)) {
        nb_team_uuids++;
    }
    return nb_team_uuids;
}

void write_team_uuids(user_t *user, FILE *fd)
{
    team_uuid_t *team_uuid = NULL;

    for (team_uuid = TAILQ_FIRST(&user->team_uuids); team_uuid != NULL;
        team_uuid = TAILQ_NEXT(team_uuid, entries)) {
        fwrite(team_uuid->uuid, sizeof(char), 36, fd);
    }
}

int count_personal_discussions(user_t *user)
{
    personal_discussion_t *personal_discussion = NULL;
    int nb_personal_discussions = 0;

    for (personal_discussion = TAILQ_FIRST(&user->discussions);
        personal_discussion != NULL;
        personal_discussion = TAILQ_NEXT(personal_discussion, entries)) {
        nb_personal_discussions++;
    }
    return nb_personal_discussions;
}

void write_personal_discussions(user_t *user, FILE *fd)
{
    personal_discussion_t *personal_discussion = NULL;

    for (personal_discussion = TAILQ_FIRST(&user->discussions);
        personal_discussion != NULL;
        personal_discussion = TAILQ_NEXT(personal_discussion, entries)) {
        fwrite(personal_discussion->uuid, sizeof(char), 36, fd);
    }
}

void write_users(FILE *fd)
{
    user_t *user = NULL;
    int nb_users = count_users();
    int nb_team_uuids = 0;
    int nb_personal_discussions = 0;
    fwrite(&nb_users, sizeof(int), 1, fd);
    for (user = TAILQ_FIRST(&global->users); user != NULL;
        user = TAILQ_NEXT(user, entries)) {
        fwrite(user->user_data, sizeof(data_t), 1, fd);
        fwrite(&user->is_logged, sizeof(bool), 1, fd);
        fwrite(&nb_team_uuids, sizeof(int), 1, fd);
        nb_team_uuids = count_team_uuids(user);
        fwrite(&nb_team_uuids, sizeof(int), 1, fd);
        write_team_uuids(user, fd);
        nb_personal_discussions = count_personal_discussions(user);
        fwrite(&nb_personal_discussions, sizeof(int), 1, fd);
        write_personal_discussions(user, fd);
    }
}

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
        printf("data->body: %s\t", data->body);
        printf("data->uuid: %s\n", data->uuid);
        bool is_logged = false;
        fread(&is_logged, sizeof(bool), 1, fd);
        printf("user->is_logged: %s\n", (is_logged == true) ? "Oui" : "Nope");
        int nb_team_uuids = 0;
        fread(&nb_team_uuids, sizeof(int), 1, fd);
        printf("nb_team_uuids: %d\n", nb_team_uuids);
        for (int j = 0; j < nb_team_uuids; j++) {
            team_uuid_t *team_uuid = malloc(sizeof(team_uuid_t));
            fread(team_uuid->uuid, sizeof(team_uuid_t), 1, fd);
            printf("team_uuid->uuid: %s\n", team_uuid->uuid);
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
