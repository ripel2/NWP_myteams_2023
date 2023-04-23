/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** user_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static int user_command_process_error(char **args, char **answer_args)
{
    if (answer_args[0] == NULL)
        return 0;
    if (strncmp(answer_args[0], "530", 3) == 0)
        client_error_unauthorized();
    if ((strncmp(answer_args[0], "430", 3) == 0 ||
    strncmp(answer_args[0], "550", 3) == 0) && args[1] != NULL) {
        string_strip_delim(&args[1], '"');
        client_error_unknown_user(args[1]);
    }
    return 0;
}

static void user_call_debug_lib(char **answer_args)
{
    if (answer_args[1] == NULL || answer_args[2] == NULL ||
    answer_args[3] == NULL)
        return;
    string_strip_delim(&answer_args[1], '"');
    string_strip_delim(&answer_args[2], '"');
    string_strip_delim(&answer_args[3], '"');
    client_print_user(answer_args[1], answer_args[2], atoi(answer_args[3]));
}

static int user_parse_answer_and_debug(char **args, char *answer)
{
    char *answer_args[7] = {NULL};

    puts(answer);
    split_string_fixed_array(answer, answer_args, 7);
    if (answer_args[0] == NULL || answer_args[1] == NULL ||
    strncmp(answer_args[0], "150", 3) != 0)
        return user_command_process_error(args, answer_args);
    user_call_debug_lib(answer_args);
    return 0;
}

int user_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "USER%s%s\n",
    args[1] == NULL ? "" : " ", args[1] == NULL ? "" : args[1]);
    ret = client_read_in_buffer(client);
    do {
        ret = client_read_in_buffer(client);
        if (ret != 0)
            return ret;
    } while (!client_flush_line(client, line));
    user_parse_answer_and_debug(args, line);
    return 0;
}
