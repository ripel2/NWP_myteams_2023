/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** tests_client_printf
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "shared.h"
#include "client.h"
#include "client_functions.h"

Test(client_printf, basic, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char buffer[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[1];
    cr_assert_eq(client_printf(&client, "test"), 0);
    read(pipefd[0], buffer, CLIENT_BUFFER_SIZE);
    cr_assert_eq(memcmp(buffer, "test", 4), 0);
    client_destroy(&client);
    close(pipefd[0]);
}

Test(client_printf, formatted, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char buffer[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[1];
    cr_assert_eq(client_printf(&client, "test %s", "test"), 0);
    read(pipefd[0], buffer, CLIENT_BUFFER_SIZE);
    cr_assert_eq(memcmp(buffer, "test test", 9), 0);
    client_destroy(&client);
    close(pipefd[0]);
}

Test(client_printf, formatted_nb, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char buffer[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[1];
    cr_assert_eq(client_printf(&client, "test %d", 42), 0);
    read(pipefd[0], buffer, CLIENT_BUFFER_SIZE);
    cr_assert_eq(memcmp(buffer, "test 42", 7), 0);
    client_destroy(&client);
    close(pipefd[0]);
}

Test(client_printf, error_1, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    cr_assert_eq(client_printf(&client, "test %d", 42), EAGAIN);
}

Test(client_printf, error_2, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    cr_assert_eq(client_printf(&client, "test %d", 42), EAGAIN);
    cr_assert_eq(client_printf(&client, "test %d", 42), EAGAIN);
}
