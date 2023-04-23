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
unsigned int write_global_struct(void);
void write_users(FILE *fd);
void write_team_uuids(FILE *fd, user_t *user);
void write_personal_discussion(FILE *fd, user_t *user);
void write_teams(FILE *fd);
void write_channels(FILE *fd, team_t *team);
void write_replies(FILE *fd, thread_t *thread);
void write_threads(FILE *fd, channel_t *channel);
unsigned int load_global_struct(void);
void write_personal_discussion(FILE *fd, user_t *user);
void read_threads(FILE *fd, channel_t *channel);
void read_teams(FILE *fd);
void read_users(FILE *fd);
void read_replies(FILE *fd, thread_t *thread);
void read_channels(FILE *fd, team_t *team);
void read_messages(FILE *fd, personal_discussion_t *discussion);
void read_personal_discussion(FILE *fd, user_t *owner);
