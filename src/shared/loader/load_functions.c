/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL : Ubuntu]
** File description:
** create_functions_array
*/

#include "loader.h"

const char *COMMAND_NAME[] = {
    "client_event_logged_in",
    "client_event_logged_out",
    "client_event_private_message_received",
    "client_event_thread_reply_received",
    "client_event_team_created",
    "client_event_channel_created",
    "client_event_thread_created",
    "client_print_users",
    "client_print_teams",
    "client_team_print_channels",
    "client_channel_print_threads",
    "client_thread_print_replies",
    "client_private_message_print_messages",
    "client_error_unknown_team",
    "client_error_unknown_channel",
    "client_error_unknown_thread",
    "client_error_unknown_user",
    "client_error_unauthorized",
    "client_error_already_exist",
    "client_print_user",
    "client_print_team",
    "client_print_channel",
    "client_print_thread",
    "client_print_team_created",
    "client_print_channel_created",
    "client_print_thread_created",
    "client_print_reply_created",
    "client_print_subscribed",
    "client_print_unsubscribed",
    "server_event_team_created",
    "server_event_channel_created",
    "server_event_thread_created",
    "server_event_reply_created",
    "server_event_user_subscribed",
    "server_event_user_unsubscribed",
    "server_event_user_created",
    "server_event_user_loaded",
    "server_event_user_logged_in",
    "server_event_user_logged_out",
    "server_event_private_message_sended",
    "client_event_thread_reply_received",
    0
};

int load_teams_library(char *pathtolib, dlloader_t *dll)
{
    dll->handle = dlopen(pathtolib, RTLD_LAZY);
    for (int i = 0; COMMAND_NAME[i]; i++) {
        *(void **)&dll->functions[i] = dlsym(dll->handle, COMMAND_NAME[i]);
        if (!dll->functions[i]) {
            printf("Error: %s", dlerror());
            return 1;
        }
    }
    return 0;
}
