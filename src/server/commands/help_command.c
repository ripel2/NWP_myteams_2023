/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** help_command
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "teams_server.h"
#include "data.h"
#include "server.h"

void handle_help(server_t *server, server_client_t *client, char **args)
{
    if (args[1] == NULL) {
        server_client_write_string(server, client, "214 myTeams commands: \n\t"
        "help\n\tlogin\n\tlogout\n\tusers\n\tuser\n\tsend\n\tmessages\n\tsubsc"
        "ribe\n\tsubscribed\n\tunsubscribe\n\tuse"
        "\n\tcreate\n\tlist\n\tinfo\n");
    } else {
        server_client_write_string(server, client, "501 Syntax error in parameters or arguments.\n");
    }
}
