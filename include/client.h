/*
** EPITECH PROJECT, 2023
** client
** File description:
** In this file for the client
*/

#pragma once

#include "data.h"

void client_event_logged_in(const char *user_uuid, const char *user_name);
void client_event_logged_out(const char *user_uuid);
void client_event_private_message_received(const char *user_uuid, const char *message);
void client_event_thread_reply_received(const char *team_uuid, const char *thread_uuid, const char *user_uuid, const char *message);
void client_event_team_created(const char *team_uuid, const char *team_name, const char *team_description);
void client_event_channel_created(const char *channel_uuid, const char *channel_name, const char *channel_description);
void client_event_thread_created(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body);
void client_print_users(const char *user_uuid, const char *user_name, int user_status);
void client_print_teams(const char *team_uuid, const char *team_name, const char *team_description);
void client_team_print_channels(const char *channel_uuid, const char *channel_name, const char *channel_description);
void client_thread_print_replies(const char *thread_uuid, const char *user_uuid, const char *reply_body);
void client_private_message_print_messages(const char *sender_uuid, const char *message_body);
void client_error_unknown_team(const char *team_uuid);
void client_error_unknown_channel(const char *channel_uuid);
void client_error_unknown_thread(const char *thread_uuid);
void client_error_unknown_user(const char *user_uuid);
void client_error_unauthorized(void);
void client_error_already_exist(void);
void client_print_user(const char *user_uuid, const char *user_name, int user_status);
void client_print_team(const char *team_uuid, const char *team_name, const char *team_description);
void client_print_channel(const char *channel_uuid, const char *channel_name, const char *channel_description);
void client_print_thread(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body);
void client_print_team_created(const char *team_uuid, const char *team_name, const char *team_description);
void client_print_channel_created(const char *channel_uuid, const char *channel_name, const char *channel_description);
void client_print_thread_created(const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body);
void client_print_reply_created(const char *thread_uuid, const char *user_uuid, const char *reply_body);
void client_print_subscribed(const char *user_uuid, const char *team_uuid);
void client_print_unsubscribed(const char *user_uuid, const char *team_uuid);
