/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** send_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int send_parse_answer_and_debug(char *answer, char **args)
{
    puts(answer);
    if (args[1] != NULL)
        string_strip_delim(&args[1], '"');
    if (args[2] != NULL)
        string_strip_delim(&args[2], '"');
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    if ((strncmp(answer, "430", 3) == 0 ||
    strncmp(answer, "550", 3) == 0) && args[1] != NULL)
        client_error_unknown_user(args[1]);
    return 0;
}

int send_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "SEND %s %s\n",
    args[1] != NULL ? args[1] : "",
    args[2] != NULL ? args[2] : "");
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    send_parse_answer_and_debug(line, args);
    return 0;
}
