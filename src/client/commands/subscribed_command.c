/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** subscribed_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static void subscribed_call_debug_lib(char **args, char **answer_args)
{
    if (answer_args[0] == NULL || answer_args[1] == NULL || answer_args[2] ==
    NULL)
        return;
    string_strip_delim(&answer_args[0], '"');
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&answer_args[2], '"');
    if (args[1] == NULL) {
        client_print_team(answer_args[0], answer_args[1], answer_args[2]);
    } else {
        client_print_users(answer_args[0], answer_args[1],
        atoi(answer_args[2]));
    }
}

static void subscribed_flush_line_loop(client_t *client, bool *needs_break,
char **args)
{
    char line[32768] = {0};
    char *answer_args[7] = {NULL};

    while (client_flush_line(client, line)) {
        puts(line);
        *needs_break = strncmp(line, "200", 3) == 0;
        if (*needs_break)
            break;
        split_string_fixed_array(line, answer_args, 7);
        subscribed_call_debug_lib(args, answer_args);
        memset(line, 0, 32768);
        memset(answer_args, 0, 7 * sizeof(char *));
    }
}

static int subscribed_command_debug_loop(client_t *client, char **args)
{
    int ret = 0;
    bool needs_break = false;

    do {
        subscribed_flush_line_loop(client, &needs_break, args);
        if (needs_break)
            break;
        FD_ZERO(&client->read_fds);
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
        subscribed_flush_line_loop(client, &needs_break, args);
    } while (!needs_break);
    return 0;
}

static int subscribed_parse_answer_and_debug(client_t *client, char *answer,
char **args)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (args[1] != NULL)
        string_strip_delim(&args[1], '"');
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    strncmp(answer_args[0], "530", 3) == 0) {
        client_error_unauthorized();
    }
    if (answer_args[0] != NULL && (strncmp(answer_args[0], "430", 3) == 0 ||
    strncmp(answer_args[0], "550", 3) == 0)) {
        client_error_unknown_team(args[1] == NULL ? "" : args[1]);
    }
    if (strncmp(answer_args[0], "150", 3) == 0) {
        return subscribed_command_debug_loop(client, args);
    }
    return 0;
}

int subscribed_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "SUBSCRIBED%s%s\n",
    args[1] == NULL ? "" : " ", args[1] == NULL ? "" : args[1]);
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    subscribed_parse_answer_and_debug(client, line, args);
    return 0;
}
