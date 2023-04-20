/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** tests_client_events
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "shared.h"
#include "client.h"
#include "client_functions.h"



Test(client_handle_event, client_event_private_message_received, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_private_message_received sender_uuid message\n", 59);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New private message from sender_uuid: [message]\n");
}

Test(client_handle_event, client_event_team_created, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_team_created team_uuid team_name team_description\n", 63);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New team created event id team_uuid: team_name (team_description)\n");
}

Test(client_handle_event, client_event_channel_created, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_channel_created channel_uuid channel_name channel_description\n", 75);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New channel created event id channel_uuid: channel_name (channel_description)\n");
}

Test(client_handle_event, client_event_thread_created, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_thread_created thread_uuid user_uuid 0 thread_title thread_body\n", 77);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New thread created event id thread_uuid by (user_uuid) at Thu Jan  1 00:00:00 1970: thread_title (thread_body)\n");
}

// this test will only work with the same timezone as the one used to run the tests
// (in this case, UTC+1)
// run with epitest.sh to make sure it works
Test(client_handle_event, client_event_thread_created_formatted_timestamp, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_thread_created thread_uuid user_uuid 1672527600 thread_title thread_body\n", 86);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New thread created event id thread_uuid by (user_uuid) at Sat Dec 31 23:00:00 2022: thread_title (thread_body)\n");
}

Test(client_handle_event, client_event_thread_reply_created, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "client_event_thread_reply_received team_uuid thread_uuid user_uuid reply_body\n", 78);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("New reply from user_uuid in thread thread_uuid of team team_uuid: [reply_body]\n");
}


Test(client_handle_event, no_valid_event, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "salut a tous c'est la salle", 28);
    cr_redirect_stderr();
    cr_assert_eq(client_handle_event(&client), 0);
    cr_assert_stderr_eq_str("");
}
