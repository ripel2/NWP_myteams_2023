/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** login_command
*/

#include "client.h"
#include "client_functions.h"
#include "logging_client.h"

static int login_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    char uuid[UUID_LENGTH + 1] = {0};

    if (args[1] != NULL && sscanf(answer, "230 %36s Logged in", uuid) == 1) {
        client_event_logged_in(uuid, args[1]);
        strcpy(client->uuid, uuid);
        strcpy(client->username, args[1]);
    }
    puts(answer);
    return 0;
}

int login_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "LOGIN %s\n", args[1] != NULL ? args[1] : "");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        login_parse_answer_and_debug(client, line, args);
    return 0;
}
