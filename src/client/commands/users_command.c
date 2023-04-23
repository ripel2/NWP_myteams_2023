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

static void users_flush_line_loop(client_t *client, bool *needs_break)
{
    char line[32768] = {0};
    char *answer_args[7] = {NULL};

    while (client_flush_line(client, line)) {
        puts(line);
        *needs_break = strncmp(line, "200", 3) == 0;
        split_string_fixed_array(line, answer_args, 7);
        users_call_debug_lib(answer_args);
        memset(line, 0, 32768);
        memset(answer_args, 0, 7 * sizeof(char *));
    }
}

static int users_command_debug_loop(client_t *client)
{
    int ret = 0;
    bool needs_break = false;

    do {
        users_flush_line_loop(client, &needs_break);
        if (needs_break)
            break;
        FD_ZERO(&client->read_fds);
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
        users_flush_line_loop(client, &needs_break);
    } while (!needs_break);
    return 0;
}

static int users_parse_answer_and_debug(client_t *client, char *answer)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    strncmp(answer_args[0], "530", 3) == 0) {
        client_error_unauthorized();
        return 0;
    }
    return users_command_debug_loop(client);
}

int users_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    (void)args;
    client_printf(client, "USERS\n");
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    users_parse_answer_and_debug(client, line);
    return 0;
}
