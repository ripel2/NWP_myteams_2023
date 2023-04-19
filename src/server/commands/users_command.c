/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** users_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

char *itoa(int number)
{
    char *str = malloc(sizeof(char) * 10);
    int i = 0;

    if (str == NULL)
        return NULL;
    if (number == 0) {
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    while (number > 0) {
        str[i] = number % 10 + '0';
        number /= 10;
        i++;
    }
    str[i] = '\0';
    return (str);
}

void handle_users(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;
    int nb_users = 0;

    (void)args;
    server_client_write_string(server, client, "150 ");
    TAILQ_FOREACH(user, &global->users, entries) {
        nb_users++;
    }
    server_client_write_string(server, client, itoa(nb_users));
    server_client_write_string(server, client, "\n");
    TAILQ_FOREACH(user, &global->users, entries) {
        server_client_write_string(server, client, user->user_data->uuid);
        server_client_write_string(server, client, " ");
        server_client_write_string(server, client, user->user_data->name);
        server_client_write_string(server, client, "\n");
    }
    server_client_write_string(server, client, "200 OK\n");
}
