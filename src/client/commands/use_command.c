/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** use_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int use_parse_answer_and_debug(char *answer)
{
    puts(answer);
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    return 0;
}

int use_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};
    char command[1024] = {0};

    strcpy(command, "USE ");
    for (size_t c = 1; c < 4; c++) {
        if (args[c] != NULL)
            strcat(command, args[c]);
        if (c < 3)
            strcat(command, " ");
    }
    strcat(command, "\n");
    client_printf(client, "%s", command);
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        use_parse_answer_and_debug(line);
    return 0;
}
