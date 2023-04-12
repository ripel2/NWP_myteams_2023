/*
** EPITECH PROJECT, 2023
** data
** File description:
** In this file for the data structure
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 32
#define UUID_LENGTH 36
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct user_s {
    char username[MAX_NAME_LENGTH + 1];
    char uuid[UUID_LENGTH + 1];
    bool is_logged;
    TAILQ_HEAD(team_uuid_list_s, team_uuid_s) team_uuids;
    TAILQ_HEAD(discussion_list_s, personal_discussion_s) discussions;
    TAILQ_ENTRY(user_s) entries;
} user_t;

typedef struct team_uuid_s {
    const char uuid[UUID_LENGTH + 1];
} team_uuid_t;

typedef struct team_s {
    const char name[MAX_NAME_LENGTH + 1];
    const char description[MAX_DESCRIPTION_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
    TAILQ_HEAD(channel_list_s, channel_s) channels;
} team_t;

typedef struct channel_s {
    const char name[MAX_NAME_LENGTH + 1];
    const char description[MAX_DESCRIPTION_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
    TAILQ_HEAD(thread_list_s, thread_s) threads;
} channel_t;

typedef struct thread_s {
    const char user_name[MAX_NAME_LENGTH + 1];
    const char user_uuid[UUID_LENGTH + 1];
    const char name[MAX_NAME_LENGTH + 1];
    const char body[MAX_BODY_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
    TAILQ_HEAD(reply_list_s, reply_s) replies;
} thread_t;

typedef struct reply_s {
    const char user_name[MAX_NAME_LENGTH + 1];
    const char user_uuid[UUID_LENGTH + 1];
    const char body[MAX_BODY_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
} reply_t;

typedef struct personal_discussion_s {
    const char user_name[MAX_NAME_LENGTH + 1];
    const char user_uuid[UUID_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
    TAILQ_HEAD(message_list_s, message_s) messages;
} personal_discussion_t;

typedef struct message_s {
    const char user_name[MAX_NAME_LENGTH + 1];
    const char user_uuid[UUID_LENGTH + 1];
    const char body[MAX_BODY_LENGTH + 1];
    const char uuid[UUID_LENGTH + 1];
} message_t;

typedef struct global_s {
    TAILQ_HEAD(user_list_s, user_s) users;
    TAILQ_HEAD(team_list_s, team_s) teams;
} global_t;
