/*
** EPITECH PROJECT, 2023
** myteams_client
** File description:
** client main loop
*/

#include "client.h"
#include "client_functions.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static const command_t COMMANDS[] = {
    {"/help", &help_command},
    {"/login", &login_command},
    {"/logout", &logout_command},
    {"/users", &users_command},
    {"/user", &user_command},
    {"/send", &send_command},
    {"/subscribe", &subscribe_command},
    {"/unsubscribe", &unsubscribe_command},
    {"/use", &use_command},
    {"/create", &create_command},
    {NULL, NULL}
};

static bool command_has_syntax_error(char *line)
{
    size_t quote_count = 0;

    for (size_t i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"')
            quote_count++;
    }
    return quote_count % 2 != 0;
}

static int client_process_command_line(client_t *client, char *line)
{
    char *args[5] = {NULL};

    if (command_has_syntax_error(line)) {
        puts("Syntax error: missing quote");
        return 0;
    }
    split_string_fixed_array(line, args, 5);
    if (args[0] == NULL)
        return 0;
    for (command_t *c = (command_t *)COMMANDS; c->name != NULL; c++) {
        if (strcmp(args[0], c->name) == 0) {
            return c->func(client, args);
        }
    }
    printf("Unknown command: \"%s\", try /help\n", args[0]);
    fflush(stdout);
    return 0;
}

int client_handle_command(client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

    if (feof(stdin)) {
        client->needs_exit = true;
        return 0;
    }
    if (read == -1)
        return errno;
    if (read > 4 && strncmp(line, "/exit", 5) == 0) {
        client->needs_exit = true;
        return 0;
    }
    if (read > 0 && line[read - 1] == '\n')
        line[read - 1] = '\0';
    return client_process_command_line(client, line);
}
