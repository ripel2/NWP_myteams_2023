/*
** EPITECH PROJECT, 2023
** thread
** File description:
** In this file for the thread function
*/

#include "data.h"

void client_event_thread_reply_received(const char *team_uuid, const char *thread_uuid, const char *user_uuid, const char *message)
{
    (void)team_uuid;
    (void)thread_uuid;
    (void)user_uuid;
    (void)message;
}

void client_event_thread_created(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body)
{
    (void)thread_uuid;
    (void)user_uuid;
    (void)thread_title;
    (void)thread_body;
}

void client_error_unknown_thread(const char *thread_uuid)
{
    (void)thread_uuid;
}

void client_print_thread(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body)
{
    (void)thread_uuid;
    (void)user_uuid;
    (void)thread_title;
    (void)thread_body;
}

void client_print_thread_created(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body)
{
    (void)thread_uuid;
    (void)user_uuid;
    (void)thread_title;
    (void)thread_body;
}

void client_print_reply_created(const char *thread_uuid, const char *user_uuid, const char *reply_body)
{
    (void)thread_uuid;
    (void)user_uuid;
    (void)reply_body;
}