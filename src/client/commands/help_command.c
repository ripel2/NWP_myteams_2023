/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** help_command
*/

#include "client.h"
#include "client_functions.h"

int help_command(client_t *client, char **args)
{
    (void)client;
    (void)args;
    printf("Pour gagner, il ne faut pas perdre.\n");
    printf("\t- Karim Benzema\n");
    return 0;
}
