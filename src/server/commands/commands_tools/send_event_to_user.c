/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** send_event_to_user
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void send_event_to_user(server_t *server, user_t *user_seeked, char *str)
{
    server_client_t *client = NULL;

    TAILQ_FOREACH(client, &server->clients, entries) {
        if (client->fd == user_seeked->socket_fd) {
            server_client_write_string(server, client, str);
            break;
        }
    }
}
