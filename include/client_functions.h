/*
** EPITECH PROJECT, 2023
** client
** File description:
** teams client functions
*/

#pragma once

#include "data.h"
#include "client.h"
#include "loader.h"

extern dlloader_t dll;

typedef struct client_info_s {
    char username[MAX_NAME_LENGTH + 1];
    char uuid[UUID_LENGTH + 1];
} client_info_t;

int teams_client_loop(client_t *client);

typedef struct command_s {
    char *name;
    int (*func)(client_t *client, client_info_t *info, char **args);
} command_t;

/**
 * @brief Get a line from the server
 * @param client The mynet client to use
 * @param result The result of the command (pointer to a line_t)
 * @return 0 if success, -1 if error
*/
int client_get_line_timeout(client_t *client, line_t **result);

/**
 * @brief Execute a command and returns the first line of the response
 * @param client The mynet client to use
 * @param cmd The command to execute
 * @param size The size of the command
 * @param result The result of the command
 * @return 0 if success, -1 if error
*/
int execute_simple_command(client_t *client, char *cmd,
size_t size, line_t **result);

int help_command(client_t *client, client_info_t *info, char **args);
int login_command(client_t *client, client_info_t *info, char **args);
int logout_command(client_t *client, client_info_t *info, char **args);
int users_command(client_t *client, client_info_t *info, char **args);
int user_command(client_t *client, client_info_t *info, char **args);
int send_command(client_t *client, client_info_t *info, char **args);
int messages_command(client_t *client, client_info_t *info, char **args);
int subscribe_command(client_t *client, client_info_t *info, char **args);
int subscribed_command(client_t *client, client_info_t *info, char **args);
int unsubscribe_command(client_t *client, client_info_t *info, char **args);
int use_command(client_t *client, client_info_t *info, char **args);
int create_command(client_t *client, client_info_t *info, char **args);
int list_command(client_t *client, client_info_t *info, char **args);
int info_command(client_t *client, client_info_t *info, char **args);
