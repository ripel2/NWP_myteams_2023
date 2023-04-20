/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** messages_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static void messages_call_debug_lib(char *from_uuid,
char **args, char **answer_args)
{
    time_t timestamp = 0;
    char *sender_uuid = NULL;

    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    answer_args[2] == NULL)
        return;
    string_strip_delim(&answer_args[0], '"');
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&answer_args[2], '"');
    timestamp = (time_t)atol(answer_args[1]);
    sender_uuid = from_uuid;
    if (strcmp(answer_args[0], "FROM") == 0)
        sender_uuid = args[1] == NULL ? "" : args[1];
    client_private_message_print_messages(sender_uuid, timestamp,
    answer_args[2]);
}

static void messages_flush_line_loop(client_t *client, bool *needs_break,
char **args)
{
    char line[32768] = {0};
    char *answer_args[7] = {NULL};

    while (client_flush_line(client, line)) {
        puts(line);
        *needs_break = strncmp(line, "200", 3) == 0;
        split_string_fixed_array(line, answer_args, 7);
        messages_call_debug_lib(client->uuid, args, answer_args);
        memset(line, 0, 32768);
        memset(answer_args, 0, 7 * sizeof(char *));
    }
}

static int messages_command_debug_loop(client_t *client, char **args)
{
    int ret = 0;
    bool needs_break = false;

    do {
        messages_flush_line_loop(client, &needs_break, args);
        if (needs_break)
            break;
        FD_ZERO(&client->read_fds);
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
        messages_flush_line_loop(client, &needs_break, args);
    } while (!needs_break);
    return 0;
}

static int messages_parse_answer_and_debug(client_t *client, char *answer,
char **args)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    strncmp(answer_args[0], "530", 3) == 0) {
        client_error_unauthorized();
    }
    if (strncmp(answer_args[0], "150", 3) == 0) {
        return messages_command_debug_loop(client, args);
    }
    return 0;
}

int messages_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "MESSAGES%s%s\n",
    args[1] == NULL ? "" : " ", args[1] == NULL ? "" : args[1]);
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    messages_parse_answer_and_debug(client, line, args);
    return 0;
}
