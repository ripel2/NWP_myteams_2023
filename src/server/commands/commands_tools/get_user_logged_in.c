/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_user_logged_in
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

user_t *get_user_logged_in(server_client_t *client)
{
    user_t *user;

    TAILQ_FOREACH(user, &global->users, entries) {
        if (user && user->is_logged == true && user->socket_fd == client->fd) {
            return user;
        }
    }
    return user;
}
