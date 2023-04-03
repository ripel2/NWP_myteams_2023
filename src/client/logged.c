/*
** EPITECH PROJECT, 2023
** logged
** File description:
** In this file for the logged function
*/

#include "data.h"
#include <stdbool.h>

void client_event_logged_in(const char *user_uuid, const char *user_name)
{
    (void)user_uuid;
    (void)user_name;
}

void client_event_logged_out(const char *user_uuid)
{
    (void)user_uuid;
}

void client_error_unauthorized(void)
{
}

void client_error_already_exist(void)
{
}
