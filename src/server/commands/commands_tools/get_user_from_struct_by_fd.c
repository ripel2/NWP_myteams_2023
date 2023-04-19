/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** get_user_from_struct_by_fd
*/

#include "shared.h"
#include "data_struct_functions.h"
#include "logging_server.h"
#include "teams_commands.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

user_t *get_user_from_struct_by_fd(int fd)
{
    user_t *tmp_user = NULL;

    TAILQ_FOREACH(tmp_user, &global->users, entries) {
        if (tmp_user && tmp_user->socket_fd == fd) {
            return tmp_user;
        }
    }
    return NULL;
}
