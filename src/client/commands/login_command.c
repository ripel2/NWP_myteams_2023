/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** login_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int login_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (answer_args[0] == NULL || answer_args[1] == NULL || args[1] == NULL ||
    strcmp(answer_args[0], "230") != 0)
        return 0;
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&args[1], '"');
    client_event_logged_in(answer_args[1], args[1]);
    strcpy(client->uuid, answer_args[1]);
    strcpy(client->username, args[1]);
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
