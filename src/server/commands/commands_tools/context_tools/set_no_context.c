/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** set_no_context
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void set_no_context(server_t *server, server_client_t *client)
{
    user_t *user = get_user_logged_in(client);

    user->context = NO_CONTEXT;
    server_client_write_string(server, client, "110 OK\n");
}
