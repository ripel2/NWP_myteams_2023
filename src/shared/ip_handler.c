/*
** EPITECH PROJECT, 2023
** ip_handler
** File description:
** In this file for the ip_handler function
*/

#include <stdbool.h>
#include <arpa/inet.h>

bool is_ip_valid(const char *ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    return result != 0;
}