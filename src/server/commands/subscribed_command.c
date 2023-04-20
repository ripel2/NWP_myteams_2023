/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** subscribed_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void handle_subscribed(server_t *server, server_client_t *client, char **args)
{
    if (args[2] != NULL) {
        server_client_write_string(server, client, "Too many arguments\n");
        return;
    }
}
