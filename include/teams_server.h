/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** teams_server
*/

#pragma once

#include "server.h"

int teams_server_loop(server_t *server);
void teams_handle_client_commands(server_t *server, server_client_t *client);
