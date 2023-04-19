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

static void use_update_client_values(client_t *client, char **args)
{
    if (args[1] != NULL) {
        string_strip_delim(&args[1], '"');
        strcpy(client->use_team_uuid, args[1]);
    }
    if (args[2] != NULL) {
        string_strip_delim(&args[2], '"');
        strcpy(client->use_channel_uuid, args[2]);
    }
    if (args[3] != NULL) {
        string_strip_delim(&args[3], '"');
        strcpy(client->use_thread_uuid, args[3]);
    }
}

static int use_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    puts(answer);
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    if (strncmp(answer, "110", 3) == 0) {
        memset(client->use_channel_uuid, 0, UUID_LENGTH + 1);
        memset(client->use_team_uuid, 0, UUID_LENGTH + 1);
        memset(client->use_thread_uuid, 0, UUID_LENGTH + 1);
        use_update_client_values(client, args);
    }
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
        use_parse_answer_and_debug(client, line, args);
    return 0;
}
