/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** subscribe_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int subscribe_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    puts(answer);
    if (args[1] != NULL)
        string_strip_delim(&args[1], '"');
    if (strncmp(answer, "200", 3) == 0)
        client_print_subscribed(client->uuid, args[1]);
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    if ((strncmp(answer, "430", 3) == 0 ||
    strncmp(answer, "550", 3) == 0) && args[1] != NULL)
        client_error_unknown_team(args[1]);
    return 0;
}

int subscribe_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "SUBSCRIBE %s\n",
    args[1] != NULL ? args[1] : "");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        subscribe_parse_answer_and_debug(client, line, args);
    return 0;
}
