/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL : Ubuntu]
** File description:
** basic_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include "loader.h"

DLLoader_t *init_dll(void)
{
    DLLoader_t *dll = malloc(sizeof(DLLoader_t));

    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

void fini_dll(DLLoader_t *dll)
{
    dlclose(dll->handle);
    free(dll);
}

Test(load_teams_library, client_event_logged_in)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_LOGGED_IN]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_logged_out)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_LOGGED_OUT]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_private_message_received)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_thread_reply_received)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_THREAD_REPLY_RECEIVED]("a", "a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_team_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_TEAM_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_channel_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_thread_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_THREAD_CREATED]("a", "a", 1, "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_users)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_USERS]("a", "a", 1);
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_teams)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAMS]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_team_print_channels)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_TEAM_PRINT_CHANNELS]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_channel_print_threads)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_CHANNEL_PRINT_THREADS]("a", "a", 1, "a", "a");
    cr_assert_eq(return_value, 58);
    fini_dll(dll);
}

Test(load_teams_library, client_thread_print_replies)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_THREAD_PRINT_REPLIES]("a", "a", 1, "a");
    cr_assert_eq(return_value, 43);
    fini_dll(dll);
}

Test(load_teams_library, client_private_message_print_messages)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES]("a", 1, "a");
    cr_assert_eq(return_value, 42);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_team)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_TEAM]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_channel)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_CHANNEL]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_thread)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_THREAD]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_user)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_USER]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unauthorized)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNAUTHORIZED]();
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_already_exist)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_ALREADY_EXIST]();
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_user)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_USER]("a", "a", 1);
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_team)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAM]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_channel)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_CHANNEL]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_thread)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_THREAD]("a", "a", 1, "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_team_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAM_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_channel_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_thread_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_THREAD_CREATED]("a", "a", 1, "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_reply_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_REPLY_CREATED]("a", "a", 1, "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_subscribed)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_SUBSCRIBED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_unsubscribed)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_UNSUBSCRIBED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_team_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_TEAM_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_channel_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_thread_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_THREAD_CREATED]("a", "a", "a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_reply_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_REPLY_CREATED]("a", "a", "a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_subscribed)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_SUBSCRIBED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_unsubscribed)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_UNSUBSCRIBED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_created)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_CREATED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_loaded)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOADED]("a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_logged_in)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOGGED_IN]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_logged_out)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOGGED_OUT]("a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_private_message_sended)
{ 
    DLLoader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_PRIVATE_MESSAGE_SENDED]("a", "a", "a");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}
