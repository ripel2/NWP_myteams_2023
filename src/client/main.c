/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet client main function
*/

#include <stdio.h>
#include <string.h>

void print_help(char *name)
{
    printf("USAGE: %s ip port\n", name);
    puts("\tip\tis the server ip address on which the server socket listens");
    puts("\tport\tis the port number on which the server socket listens");
}

int main(int ac, char **av)
{
    if (ac > 1 && !strcmp(av[1], "-help")) {
        print_help(av[0]);
        return 0;
    }
    if (ac != 3) {
        print_help(av[0]);
        return 84;
    }
    return 0;
}
