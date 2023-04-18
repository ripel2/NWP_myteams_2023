/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** logout_command
*/

#include "client.h"
#include "client_functions.h"
#include "logging_client.h"

static int logout_parse_answer_and_debug(client_t *client, char *answer)
{
    char uuid[UUID_LENGTH + 1] = {0};

    if (sscanf(answer, "221 %36s Logged out", uuid) == 1) {
        client_event_logged_out(uuid, client->username);
        memset(client->uuid, 0, UUID_LENGTH + 1);
        memset(client->username, 0, MAX_NAME_LENGTH + 1);
    } else if (strncmp(answer, "530", 3) == 0) {
        client_error_unauthorized();
    }
    puts(answer);
    return 0;
}

int logout_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    (void)args;
    client_printf(client, "LOGOUT\n");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        logout_parse_answer_and_debug(client, line);
    return 0;
}
