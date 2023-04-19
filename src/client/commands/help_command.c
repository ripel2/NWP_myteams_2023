/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** help_command
*/

#include "client.h"
#include "client_functions.h"

static int help_print_answer(char *answer)
{
    puts("MyTeams");
    puts("Server supported commands:");
    puts(answer);
    return 0;
}

int help_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    (void)args;
    client_printf(client, "HELP\n");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        help_print_answer(line);
    return 0;
}
