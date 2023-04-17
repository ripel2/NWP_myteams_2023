/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** data_struct_functions
*/

#pragma once

#include "data.h"

int add_user_to_struct(data_t *user_data);
user_t *get_user_from_struct(const char *uuid);
int add_team_to_struct(data_t *team_data);
team_t *get_team_from_struct(const char *uuid);
int add_channel_to_struct(const char *team_uuid, data_t *channel_data);
channel_t *get_channel_from_struct(const char *uuid);
int add_thread_to_struct(const char *channel_uuid, data_t *user_data,
data_t *thread_data);
thread_t *get_thread_from_struct(const char *uuid);
int add_reply_to_struct(const char *thread_uuid, data_t *user_data,
data_t *reply_data);
reply_t *get_reply_from_struct(const char *uuid);
int add_personnal_discussion_to_struct(char *discussion_uuid,
char *current_user_uuid, data_t *user_data);
personal_discussion_t *get_personnal_discussion_from_struct(const char *uuid);
int add_message_to_struct(data_t *sender_uuid, data_t *receiver_uuid,
data_t *message);
int add_user_to_team(const char *team_uuid, const char *user_uuid);
int remove_user_from_team(const char *team_uuid, const char *user_uuid);
bool is_channel_in_team(const char *channel_uuid, const char *team_uuid);
bool is_thread_in_channel(const char *thread_uuid, const char *channel_uuid);

char *generate_uuid(char *uuid);
data_t *init_data(char *name, char *description, char *body, char *uuid);
