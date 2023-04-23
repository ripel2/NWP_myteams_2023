/*
** EPITECH PROJECT, 2023
** client
** File description:
** teams client functions
*/

#pragma once

#include "data.h"
#include "client.h"

/**
 * @brief Main loop of the client
 * @param client The client
 * @return 0 on success, 84 on error
*/
int client_loop(client_t *client);

// Typedef for function pointers
typedef struct command_s {
    char *name;
    int (*func)(client_t *client, char **args);
} command_t;

/**
 * @brief Handle the events received from the server
 * @param client The client
 * @return 0 on success, errno on error
*/
int client_handle_event(client_t *client);
/**
 * @brief Handle the commands entered by the user
 * @param client The client
 * @return 0 on success, errno on error
*/
int client_handle_command(client_t *client);

int help_command(client_t *client, char **args);
int login_command(client_t *client, char **args);
int logout_command(client_t *client, char **args);
int users_command(client_t *client, char **args);
int user_command(client_t *client, char **args);
int send_command(client_t *client, char **args);
int messages_command(client_t *client, char **args);
int subscribe_command(client_t *client, char **args);
int subscribed_command(client_t *client, char **args);
int unsubscribe_command(client_t *client, char **args);
int use_command(client_t *client, char **args);
int create_command(client_t *client, char **args);
int list_command(client_t *client, char **args);
int info_command(client_t *client, char **args);
