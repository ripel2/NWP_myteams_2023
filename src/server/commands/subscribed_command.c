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
#include "teams_commands.h"
#include "data.h"
#include "server.h"

static int count_nb_teams(user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    int nb_teams = 0;

    TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
        nb_teams++;
    }
    return nb_teams;
}

static int count_nb_users_in_team(char *team_uuid_to_seek)
{
    team_uuid_t *team_uuid = NULL;
    user_t *user = NULL;
    int nb_users = 0;

    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
            if (strcmp(team_uuid_to_seek, team_uuid->uuid) == 0) {
                nb_users++;
            }
        }
    }
    return nb_users;
}

static void display_users_in_team(server_t *server, server_client_t *client,
char *uuid)
{
    team_uuid_t *team_uuid = NULL;
    user_t *user = NULL;

    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
            if (strcmp(uuid, team_uuid->uuid) == 0) {
                server_client_printf(server, client, "%s %s\n", user->user_data->uuid, user->user_data->name);
            }
        }
    }
}

static void handle_subscribed_with_uuid(server_t *server, server_client_t *client,
char *uuid, user_t *user)
{
    if (is_user_in_team(user, uuid) == false) {
        server_client_write_string(server, client, "431 Cannot perform action\n");
        return;
    }
    server_client_printf(server, client, "150 %d\n", count_nb_users_in_team(uuid));
    display_users_in_team(server, client, uuid);
}

static void handle_subscribed_without_uuid(server_t *server, server_client_t *client, user_t *user)
{
    team_uuid_t *team_uuid = NULL;
    team_t *team = NULL;

    server_client_printf(server, client, "150 %d\n", count_nb_teams(user));
    TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
        team = get_team_from_struct(team_uuid->uuid);
        server_client_printf(server, client, "%s %s %s\n", team->team_data->uuid, team->team_data->name, team->team_data->description);
    }
    server_client_write_string(server, client, "200 OK\n");
}

void handle_subscribed(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;

    if (args[2] != NULL) {
        server_client_write_string(server, client,
        "501 Syntax error in parameters or arguments\n");
        return;
    }
    user = get_user_logged_in(client);
    if (user == NULL) {
        server_client_write_string(server, client, "530 Not logged in\n");
        return;
    }
    if (args[1] == NULL) {
        handle_subscribed_without_uuid(server, client, user);
    } else {
        remove_bad_char(args[1]);
        string_strip_delim(&args[1], '"');
        handle_subscribed_with_uuid(server, client, args[1], user);
    }
}
