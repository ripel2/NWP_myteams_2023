/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** users_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int users_command_process_error(char **answer_args)
{
    if (answer_args[0] == NULL)
        return 0;
    if (strncmp(answer_args[0], "530", 3) == 0)
        client_error_unauthorized();
    return 0;
}

static void users_call_debug_lib(char **answer_args)
{
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    answer_args[2] == NULL)
        return;
    string_strip_delim(&answer_args[0], '"');
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&answer_args[2], '"');
    client_print_users(answer_args[0], answer_args[1], atoi(answer_args[2]));
}

static int users_command_debug_loop(client_t *client)
{
    char line[32768] = {0};
    char *answer_args[7] = {NULL};
    int ret = 0;

    do {
        memset(line, 0, 32768);
        memset(answer_args, 0, 7 * sizeof(char *));
        FD_ZERO(&client->read_fds);
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
        if (client_flush_line(client, line) == false)
            continue;
        puts(line);
        if (strncmp(line, "200", 3) == 0)
            break;
        split_string_fixed_array(line, answer_args, 7);
        users_call_debug_lib(answer_args);
    } while (true);
    return 0;
}

static int users_parse_answer_and_debug(client_t *client, char *answer)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    strncmp(answer_args[0], "150", 3) != 0)
        return users_command_process_error(answer_args);
    return users_command_debug_loop(client);
}

int users_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    (void)args;
    client_printf(client, "USERS\n");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        users_parse_answer_and_debug(client, line);
    return 0;
}
