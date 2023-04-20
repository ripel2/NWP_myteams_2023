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
#define ERROR 84
#define SUCCESS 0

enum context_enum
{
    NO_CONTEXT,
    TEAMS,
    CHANNELS,
    THREADS
};

typedef struct data_s
{
    char name[MAX_NAME_LENGTH + 1];
    char body[MAX_BODY_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    char uuid[UUID_LENGTH + 1];
} data_t;

typedef struct context_s
{
    enum context_enum user_context;
    char team_uuid[UUID_LENGTH + 1];
    char channel_uuid[UUID_LENGTH + 1];
    char thread_uuid[UUID_LENGTH + 1];
} context_t;

typedef struct user_s
{
    data_t *user_data;
    context_t *context;
    int socket_fd;
    bool is_logged;
    TAILQ_HEAD(team_uuid_list_s, team_uuid_s)
    team_uuids;
    TAILQ_HEAD(discussion_list_s, personal_discussion_s)
    discussions;
    TAILQ_ENTRY(user_s)
    entries;
} user_t;

typedef struct team_uuid_s
{
    char uuid[UUID_LENGTH + 1];
    TAILQ_ENTRY(team_uuid_s)
    entries;
} team_uuid_t;

typedef struct team_s
{
    data_t *team_data;
    TAILQ_HEAD(channel_list_s, channel_s)
    channels;
    TAILQ_ENTRY(team_s)
    entries;
} team_t;

typedef struct channel_s
{
    data_t *channel_data;
    TAILQ_HEAD(thread_list_s, thread_s)
    threads;
    TAILQ_ENTRY(channel_s)
    entries;
} channel_t;

typedef struct thread_s
{
    data_t *user_data;
    data_t *thread_data;
    TAILQ_HEAD(reply_list_s, reply_s)
    replies;
    TAILQ_ENTRY(thread_s)
    entries;
} thread_t;

typedef struct reply_s
{
    data_t *user_data;
    data_t *reply_data;
    TAILQ_ENTRY(reply_s)
    entries;
} reply_t;

typedef struct personal_discussion_s
{
    data_t *user_data;
    char uuid[UUID_LENGTH + 1];
    TAILQ_HEAD(message_list_s, message_s)
    messages;
    TAILQ_ENTRY(personal_discussion_s)
    entries;
} personal_discussion_t;

typedef struct message_s
{
    data_t *user_data;
    data_t *message_data;
    TAILQ_ENTRY(message_s)
    entries;
} message_t;

typedef struct global_s
{
    TAILQ_HEAD(user_list_s, user_s)
    users;
    TAILQ_HEAD(team_list_s, team_s)
    teams;
} global_t;

extern global_t *global;
