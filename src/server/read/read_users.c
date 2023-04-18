/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** load_struct_from_file
*/

#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "logging_server.h"
#include "data_struct_functions.h"

void read_messages(FILE *fd, user_t *user)
{
    unsigned int nb_messages = 0;
    message_t *message = NULL;

    fread(&nb_messages, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_messages; i++) {
        message = malloc(sizeof(message_t));
        message->user_data = malloc(sizeof(data_t));
        message->message_data = malloc(sizeof(data_t));
        fread(message->user_data, sizeof(data_t), 1, fd);
        fread(message->message_data, sizeof(data_t), 1, fd);
        add_message_to_struct(user->user_data, message->user_data, message->message_data);
    }
}

void read_team_uuids(FILE *fd)
{
    unsigned int nb_team_uuids = 0;
    char *uuid = NULL;

    fread(&nb_team_uuids, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_team_uuids; i++) {
        uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        fread(uuid, sizeof(char) * UUID_LENGTH + 1, 1, fd);
        printf("uuid: %s", uuid);
        free(uuid);
    }
}

void read_personal_discussion(FILE *fd, user_t *owner)
{
    unsigned int nb_personal_discussion = 0;
    data_t *user_data = NULL;
    char *uuid = NULL;
    char *discussion_uuid = NULL;

    fread(&nb_personal_discussion, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_personal_discussion; i++) {
        user_data = malloc(sizeof(data_t));
        fread(user_data, sizeof(data_t), 1, fd);
        uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        fread(uuid, sizeof(char) * UUID_LENGTH + 1, 1, fd);
        discussion_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
        generate_uuid(discussion_uuid);
        add_personnal_discussion_to_struct(discussion_uuid, owner->user_data->uuid, user_data);
        read_messages(fd, owner);
    }
}

void read_users(FILE *fd)
{
    unsigned int nb_users = 0;
    user_t *user = NULL;

    fread(&nb_users, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_users; i++) {
        user = malloc(sizeof(user_t));
        user->user_data = malloc(sizeof(data_t));
        fread(user->user_data, sizeof(data_t), 1, fd);
        fread(&user->is_logged, sizeof(bool), 1, fd);
        add_user_to_struct(init_data(user->user_data->name,
            user->user_data->description, user->user_data->body,
            user->user_data->uuid));
        server_event_user_loaded(user->user_data->uuid, user->user_data->name);
        read_team_uuids(fd);
        read_personal_discussion(fd, user);
        free(user->user_data);
        free(user);
    }
}

void read_replies(FILE *fd, thread_t *thread)
{
    unsigned int nb_replies = 0;
    reply_t *reply = NULL;

    fread(&nb_replies, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_replies; i++) {
        reply = malloc(sizeof(reply_t));
        reply->user_data = malloc(sizeof(data_t));
        reply->reply_data = malloc(sizeof(data_t));
        fread(reply->user_data, sizeof(data_t), 1, fd);
        fread(reply->reply_data, sizeof(data_t), 1, fd);
        add_reply_to_struct(thread->thread_data->uuid, reply->user_data, reply->reply_data);
        free(reply->user_data);
        free(reply->reply_data);
        free(reply);
    }
}

void read_threads(FILE *fd, channel_t *channel)
{
    unsigned int nb_threads = 0;
    thread_t *thread = NULL;

    fread(&nb_threads, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_threads; i++) {
        thread = malloc(sizeof(thread_t));
        thread->user_data = malloc(sizeof(data_t));
        thread->thread_data = malloc(sizeof(data_t));
        fread(thread->user_data, sizeof(data_t), 1, fd);
        fread(thread->thread_data, sizeof(data_t), 1, fd);
        add_thread_to_struct(channel->channel_data->uuid, thread->user_data, thread->thread_data);
        read_replies(fd, thread);
        free(thread->user_data);
        free(thread->thread_data);
        free(thread);
    }
}

void read_channels(FILE *fd, team_t *team)
{
    unsigned int nb_channels = 0;
    channel_t *channel = NULL;

    fread(&nb_channels, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_channels; i++) {
        channel = malloc(sizeof(channel_t));
        channel->channel_data = malloc(sizeof(data_t));
        fread(channel->channel_data, sizeof(data_t), 1, fd);
        add_channel_to_struct(team->team_data->uuid, channel->channel_data);
        read_threads(fd, channel);
        free(channel->channel_data);
        free(channel);
    }
}

void read_teams(FILE *fd)
{
    unsigned int nb_teams = 0;
    team_t *team = NULL;

    fread(&nb_teams, sizeof(unsigned int), 1, fd);
    for (unsigned int i = 0; i < nb_teams; i++) {
        team = malloc(sizeof(team_t));
        team->team_data = malloc(sizeof(data_t));
        fread(team->team_data, sizeof(data_t), 1, fd);
        add_team_to_struct(team->team_data);
        read_channels(fd, team);
        free(team->team_data);
        free(team);
    }
}

unsigned int load_global_struct(void)
{
    FILE *fd = NULL;

    fd = open_file("my_teams.db", "r");
    if (fd == NULL)
        return ERROR;
    read_users(fd);
    read_teams(fd);
    fclose(fd);
    return SUCCESS;
}