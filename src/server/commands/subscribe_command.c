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
#include "teams_commands.h"
#include "logging_server.h"

static bool check_if_user_is_logged_in(server_client_t *client)
{
    user_t *tmp_user = NULL;

    TAILQ_FOREACH(tmp_user, &global->users, entries) {
        if (tmp_user && tmp_user->is_logged == true && (fd_tmp == client->fd))
            return true;
    }
    return false;
}

static bool requirement_ok(server_t *server, server_client_t *client,
char **args)
{
    team_t *team = NULL;

    if (args[1] == NULL || args[2] != NULL) {
        server_client_printf(server, client, "501 Invalid arguments\n");
        return false;
    }
    if (check_if_user_is_logged_in(client) == false) {
        server_client_printf(server, client, "430 User not logged in\n");
        return false;
    }
    team = get_team_from_struct(args[1]);
    if (team == NULL) {
        server_client_printf(server, client, "430 Team doesn't exist\n");
        return false;
    }
    return true;
}

static bool check_uuid(server_t *server, server_client_t *client, char **args)
{
    if (is_a_uuid(args[1]) == false) {
        server_client_printf(server, client, "550 Bad UUID\n");
        return false;
    }
    return true;
}

void handle_subscribe(server_t *server, server_client_t *client,
char **args)
{
    user_t *user = NULL;

    user = get_user_logged_in(client);
    if (requirement_ok(server, client, args) == false)
        return;
    remove_bad_char(args[1]);
    string_strip_delim(&args[1], '"');
    if (check_uuid(server, client, args) == false)
        return;
    if (user == NULL) {
        server_client_printf(server, client, "430 User doesn't exist\n");
        return;
    }
    if (add_user_to_team(args[1], user->user_data->uuid) == 84) {
        server_client_printf(server, client, "500 Internal server error\n");
        return;
    }
    server_event_user_subscribed(args[1], user->user_data->uuid);
    server_client_printf(server, client, "200 Subscribed to team %s", args[1]);
}
