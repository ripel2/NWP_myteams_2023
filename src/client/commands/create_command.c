/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** create_command
*/

#include "client.h"
#include "shared.h"
#include "client_functions.h"
#include "logging_client.h"

static void create_call_debug_switch(client_t *client, char *created_uuid,
char **args, int use_status)
{
    time_t now = time(NULL);

    switch (use_status) {
    case 0:
        client_print_team_created(created_uuid, args[1], args[2]);
        break;
    case 1:
        client_print_channel_created(created_uuid, args[1], args[2]);
        break;
    case 2:
        client_print_thread_created(created_uuid, client->uuid, now,
        args[1], args[2]);
        break;
    case 3:
        client_print_reply_created(client->use_thread_uuid, client->uuid,
        now, args[1]);
        break;
    }
}

static int create_call_debug(client_t *client, char *answer, char **args)
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
    create_call_debug_switch(client, answer_args[1], args, use_status);
    return 0;
}

static int create_parse_answer_and_debug(client_t *client,
char *answer, char **args)
{
    puts(answer);
    if (args[1] != NULL)
        string_strip_delim(&args[1], '"');
    if (args[2] != NULL)
        string_strip_delim(&args[2], '"');
    if (strncmp(answer, "530", 3) == 0)
        client_error_unauthorized();
    if (strncmp(answer, "451", 3) == 0)
        client_error_already_exist();
    if (strncmp(answer, "150", 3) == 0)
        create_call_debug(client, answer, args);
    return 0;
}

int create_command(client_t *client, char **args)
{
    int ret = 0;
    char line[32768] = {0};

    client_printf(client, "CREATE %s %s\n",
    args[1] != NULL ? args[1] : "",
    args[2] != NULL ? args[2] : "");
    ret = client_read_in_buffer(client);
    if (ret != 0)
        return ret;
    if (client_flush_line(client, line))
        create_parse_answer_and_debug(client, line, args);
    return 0;
}
