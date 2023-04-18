/*
** EPITECH PROJECT, 2023
** save
** File description:
** In this file for the save function
*/

#pragma once

#include <stdio.h>
#include "data.h"

FILE *open_file(const char *path, const char *mode);
unsigned int write_global(void);
void write_users(FILE *fd);
int count_team_uuids(user_t *user);
void write_team_uuids(FILE *fd, user_t *user);
void write_personal_discussion(FILE *fd, user_t *user);
void write_teams(FILE *fd);
void write_channels(FILE *fd, team_t *team);
void write_replies(FILE *fd, thread_t *thread);
void write_threads(FILE *fd, channel_t *channel);
