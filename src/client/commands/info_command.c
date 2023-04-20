/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** info_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static void info_call_debug_switch(client_t *client, char *return_uuid,
char **args, int use_status)
{
    switch (use_status) {
    case 0:
        client_print_user(client->uuid, client->username, 1);
        break;
    }
}

static int info_call_debug(client_t *client, char *answer, char **args)
{
    char *answer_args[4] = {NULL};
    int use_status = 0;

    split_string_fixed_array(answer, answer_args, 4);
    if (answer_args[1] == NULL)
        return 0;
    string_strip_delim(&answer_args[1], '"');
    use_status = client->use_team_uuid[0] != '\0' ? 1 : 0;
    use_status += client->use_channel_uuid[0] != '\0' ? 1 : 0;
    use_status += client->use_thread_uuid[0] != '\0' ? 1 : 0;
    if (use_status > 0 && answer_args[2] == NULL)
        return 0;
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&answer_args[2], '"');
    info_call_debug_switch(client, answer_args[1], args, use_status);
    return 0;
}

static void info_call_debug_error(client_t *client)
{
    int use_status = 0;

    use_status = client->use_team_uuid[0] != '\0' ? 1 : 0;
    use_status += client->use_channel_uuid[0] != '\0' ? 1 : 0;
    use_status += client->use_thread_uuid[0] != '\0' ? 1 : 0;
    switch (use_status) {
    case 1:
        client_error_unknown_team(client->use_team_uuid);
        break;
    case 2:
        client_error_unknown_channel(client->use_channel_uuid);
        break;
    case 3:
        client_error_unknown_thread(client->use_thread_uuid);
        break;
    }
}

static int info_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    puts(answer);
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    if (strncmp(answer, "430", 3) == 0)
        info_call_debug_error(client);
    if (strncmp(answer, "150", 3) == 0)
        info_call_debug(client, answer, args);
    return 0;
}

int info_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "INFO\n");
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    info_parse_answer_and_debug(client, line, args);
    return 0;
}
