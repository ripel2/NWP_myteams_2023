/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** subscribe_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void handle_subscribe(server_t *server, server_client_t *client, char **args)
{
    (void)server;
    (void)client;
    server_client_write_string(server, client, "Command: ");
    server_client_write_string(server, client, args[0]);
    server_client_write_string(server, client, "\n");
    server_client_write_string(server, client, "Arguments: ");
    for (int i = 1; args[i]; i++) {
        server_client_write_string(server, client, args[i]);
        server_client_write_string(server, client, " ");
    }
}