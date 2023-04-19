/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** user_command
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

static bool is_a_uuid(char *str)
{
    if (strlen(str) != 36)
        return false;
    if (str[8] != '-' || str[13] != '-'
    || str[18] != '-' || str[23] != '-')
        return false;
    return true;
}

void handle_user(server_t *server, server_client_t *client, char **args)
{
    user_t *user = NULL;

    if (args[1] == NULL) {
        server_client_printf(server, client, "501 Invalid arguments\n");
        return;
    }
    remove_bad_char(args[1]);
    string_strip_delim(&args[1], '"');
    if (is_a_uuid(args[1]) == false) {
        server_client_printf(server, client, "550 Bad UUID\n");
        return;
    }
    user = get_user_from_struct(args[1]);
    if (user == NULL) {
        server_client_printf(server, client, "430 User doesn't exist\n");
        return;
    }
    server_client_printf(server, client, "150 %s %s %c\n",
    user->user_data->uuid, user->user_data->name,
    (user->is_logged ? '1' : '0'));
}
