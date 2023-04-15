/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL : Ubuntu]
** File description:
** basic_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include "loader.h"

dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

void fini_dll(dlloader_t *dll)
{
    dlclose(dll->handle);
    free(dll);
}

void redirect_all_stderr(void)
{
    cr_redirect_stderr();
}

Test(load_teams_library, client_event_logged_in, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_LOGGED_IN]("a", "a");
    cr_assert_stderr_eq_str("Client a logged in with login a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_logged_out, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_LOGGED_OUT]("a", "a");
    cr_assert_stderr_eq_str("Client a logged out with login a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_private_message_received, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED]("a", "a");
    cr_assert_stderr_eq_str("New private message from a: [a]\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_thread_reply_received, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_THREAD_REPLY_RECEIVED]("a", "a", "a", "a");
    cr_assert_stderr_eq_str("New reply from a in thread a of team a: [a]\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_team_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_TEAM_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("New team created event id a: a (a)\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_channel_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("New channel created event id a: a (a)\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_event_thread_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_EVENT_THREAD_CREATED]("a", "a", 1, "a", "a");
    cr_assert_stderr_eq_str("New thread created event id a by (a) at Thu Jan  1 00:00:01 1970: a (a)\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_users, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_USERS]("a", "a", 1);
    cr_assert_stderr_eq_str("User \"a\" (a): 1\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_teams, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAMS]("a", "a", "a");
    cr_assert_stderr_eq_str("Team \"a\" (a): a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_team_print_channels, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_TEAM_PRINT_CHANNELS]("a", "a", "a");
    cr_assert_stderr_eq_str("Channel \"a\" (a): a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_channel_print_threads, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_CHANNEL_PRINT_THREADS]("a", "a", 1, "a", "a");
    cr_assert_stderr_eq_str("[Thread a] Created by a (Thu Jan  1 00:00:01 1970): a [a]\n");
    cr_assert_eq(return_value, 58);
    fini_dll(dll);
}

Test(load_teams_library, client_thread_print_replies, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_THREAD_PRINT_REPLIES]("a", "a", 1, "a");
    cr_assert_stderr_eq_str("[Thread a] a (Thu Jan  1 00:00:01 1970): a\n");
    cr_assert_eq(return_value, 43);
    fini_dll(dll);
}

Test(load_teams_library, client_private_message_print_messages, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES]("a", 1, "a");
    cr_assert_stderr_eq_str("[Private] a (Thu Jan  1 00:00:01 1970): a\n");
    cr_assert_eq(return_value, 42);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_team, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_TEAM]("a");
    cr_assert_stderr_eq_str("Unknown team a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_channel, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_CHANNEL]("a");
    cr_assert_stderr_eq_str("Unknown channel a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_thread, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_THREAD]("a");
    cr_assert_stderr_eq_str("Unknown thread a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unknown_user, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNKNOWN_USER]("a");
    cr_assert_stderr_eq_str("Unknown user a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_unauthorized, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_UNAUTHORIZED]();
    cr_assert_stderr_eq_str("Unauthorized: action prohibited\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_error_already_exist, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_ERROR_ALREADY_EXIST]();
    cr_assert_stderr_eq_str("Already exist: action prohibited\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_user, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_USER]("a", "a", 1);
    cr_assert_stderr_eq_str("User \"a\" (a): 1\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_team, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAM]("a", "a", "a");
    cr_assert_stderr_eq_str("Team \"a\" (a): a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_channel, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_CHANNEL]("a", "a", "a");
    cr_assert_stderr_eq_str("Channel \"a\" (a): a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_thread, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_THREAD]("a", "a", 1, "a", "a");
    cr_assert_stderr_eq_str("Thread \"a\" created by a (Thu Jan  1 00:00:01 1970): a [a]\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_team_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_TEAM_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("[Team a] Created a, a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_channel_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("[Channel a] Created a, a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_thread_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_THREAD_CREATED]("a", "a", 1, "a", "a");
    cr_assert_stderr_eq_str("[Thread a] Created created by a (Thu Jan  1 00:00:01 1970): a [a]\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_reply_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_REPLY_CREATED]("a", "a", 1, "a");
    cr_assert_stderr_eq_str("[Reply] Created in thread a by a (Thu Jan  1 00:00:01 1970): a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_subscribed, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_SUBSCRIBED]("a", "a");
    cr_assert_stderr_eq_str("[Subscribed] a to a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, client_print_unsubscribed, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[CLIENT_PRINT_UNSUBSCRIBED]("a", "a");
    cr_assert_stderr_eq_str("[Unsubscribed] a to a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_team_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_TEAM_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("User a created Team \"a\" (a).\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_channel_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_CHANNEL_CREATED]("a", "a", "a");
    cr_assert_stderr_eq_str("Channel \"a\" (a) created in team a.\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_thread_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_THREAD_CREATED]("a", "a", "a", "a", "a");
    cr_assert_stderr_eq_str("New thread a in channel a.\nNew reply in thread a (a) from a: a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_reply_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_REPLY_CREATED]("a", "a", "a", "a", "a");
    cr_assert_stderr_eq_str("New reply in thread (a) from a: a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_subscribed, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_SUBSCRIBED]("a", "a", "a");
    cr_assert_stderr_eq_str("User a subscribed to a.\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_unsubscribed, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_UNSUBSCRIBED]("a", "a");
    cr_assert_stderr_eq_str("User a unsubscribe from a.\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_created, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_CREATED]("a", "a");
    cr_assert_stderr_eq_str("New user: a (a).\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_loaded, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOADED]("a", "a");
    cr_assert_stderr_eq_str("User loaded: a (a).\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_logged_in, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOGGED_IN]("a");
    cr_assert_stderr_eq_str("User a logged in.\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_user_logged_out, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_USER_LOGGED_OUT]("a");
    cr_assert_stderr_eq_str("User a logged out.\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}

Test(load_teams_library, server_event_private_message_sended, .init=redirect_all_stderr)
{
    dlloader_t *dll = init_dll();
    int return_value = dll->functions[SERVER_EVENT_PRIVATE_MESSAGE_SENDED]("a", "a", "a");
    cr_assert_stderr_eq_str("Private message a->a: a\n");
    cr_assert_eq(return_value, 1);
    fini_dll(dll);
}
