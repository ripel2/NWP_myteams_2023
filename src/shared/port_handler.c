/*
** EPITECH PROJECT, 2023
** port_handling
** File description:
** In this file he have the function to check if the port is valid
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_port_valid(const char *port)
{
    bool is_valid = true;
    int port_number = atoi(port);

    if (port_number == -1) {
        fprintf(stderr, "Your port number is not valid it must be a number");
        is_valid = false;
    }
    if (port_number < 0 || port_number > 65535) {
        fprintf(stderr, "Your port number is not valid it must be between 0 and 65535");
        is_valid = false;
    }
    return is_valid;
}
