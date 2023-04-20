/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** teams_commands
*/

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void handle_help(server_t *server, server_client_t *client, char **args);
void handle_login(server_t *server, server_client_t *client, char **args);
void handle_logout(server_t *server, server_client_t *client, char **args);
void handle_users(server_t *server, server_client_t *client, char **args);
void handle_user(server_t *server, server_client_t *client, char **args);
void handle_send(server_t *server, server_client_t *client, char **args);
void handle_messages(server_t *server, server_client_t *client, char **args);
void handle_subscribe(server_t *server, server_client_t *client, char **args);
void handle_subscribed(server_t *server, server_client_t *client, char **args);
void handle_unsubscribe(server_t *server, server_client_t *client, char **args);
void handle_use(server_t *server, server_client_t *client, char **args);
void handle_create(server_t *server, server_client_t *client, char **args);
void handle_list(server_t *server, server_client_t *client, char **args);
void handle_info(server_t *server, server_client_t *client, char **args);

bool is_user_already_logged_in(server_t *server, server_client_t *client);
char *remove_bad_char(char *str);
user_t *get_user_logged_in(server_client_t *client);
user_t *get_user_from_struct_by_fd(int fd);
void send_event_to_user(server_t *server, user_t *user_seeked, char *str);
bool is_a_uuid(char *str);
int count_nb_messages(user_t *current_user, user_t *user_to_seek);
void set_channel_context(server_t *server, server_client_t *client,
char **args);
void set_no_context(server_t *server, server_client_t *client,
char **args);
void set_teams_context(server_t *server, server_client_t *client,
char **args);
void set_thread_context(server_t *server, server_client_t *client,
char **args);
