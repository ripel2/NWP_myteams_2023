/*
** EPITECH PROJECT, 2023
** myteams_cli
** File description:
** myteams_cli main function
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "shared.h"
#include "data.h"
#include "client.h"
#include "client_functions.h"

// list of commands with their corresponding function
// char * and function that takes a client_t and a char ** as parameters and returns an int
static const command_t COMMANDS[] = {
    {"help", &help_command},
    {"login", &login_command},
    {"logout", &logout_command},
    {"users", &users_command},
    {"user", &user_command},
    {"send", &send_command},
    {"messages", &messages_command},
    {"subscribe", &subscribe_command},
    {"subscribed", &subscribed_command},
    {"unsubscribe", &unsubscribe_command},
    {"use", &use_command},
    {"create", &create_command},
    {"list", &list_command},
    {"info", &info_command},
    {NULL, NULL}
};

int teams_client_loop(client_t *client)
{
    (void)client;
    (void)COMMANDS;
    return 0;
}
