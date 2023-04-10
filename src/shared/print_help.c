/*
** EPITECH PROJECT, 2023
** print_help
** File description:
** In this file he have the function to print the help
*/

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static void print_server_help(void)
{
    printf("USAGE: ./myteams_server port\n"
    "\tport is the port number on which the server socket listens.\n");
}

static void print_client_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n"
    "\tip is the server ip address on which the server socket listens\n"
    "\tport is the port number on which the server socket listens.\n");
}

static unsigned short get_type(char **av)
{
    enum { SERVER, CLIENT, ERROR };
    if (av[0] != NULL && strstr(av[0], "myteams_server") != NULL)
        return SERVER;
    else if (av[0] != NULL && strstr(av[0], "myteams_cli") != NULL)
        return CLIENT;
    return ERROR;
}

bool print_help_if_needed(int ac, char **av)
{
    enum { SERVER, CLIENT, ERROR };
    unsigned short what_type = get_type(av);

    if (what_type == SERVER && ac != 2) {
        print_server_help();
        return true;
    }
    if (what_type == CLIENT && ac != 3) {
        print_client_help();
        return true;
    }
    if (av[1] != NULL && (strcmp(av[1], "-help") == 0
        || strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0)) {
        if (what_type == SERVER)
            print_server_help();
        if (what_type == CLIENT)
            print_client_help();
        return true;
    }
    return false;
}
