/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** tests_buffer_managment
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "shared.h"
#include "client.h"
#include "client_functions.h"

Test(client_read_in_buffer, basic, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\n", 5);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(memcmp(client.buffer, "test\n", 5), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_read_in_buffer, splitted, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\ntest", 9);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(memcmp(client.buffer, "test\ntest", 5), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, basic, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\n", 5);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "test", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "", 1), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, splitted, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\ntest", 9);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "test", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "test", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, splitted_multiple, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\nabcd\nefgh", 14);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "test", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "abcd\nefgh", 9), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, multiple_writes, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\nab", 7);
    write(pipefd[1], "cd\nefgh", 7);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "test", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "abcd\nefgh", 9), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, multiple_writes_flushed, .timeout = 3) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "test\nab", 7);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "test", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "ab", 2), 0);
    write(pipefd[1], "cd\nefgh", 7);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, five_flush, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "abcd\nefgh\nijkl\nmnop\nqrst\n", 25);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh\nijkl\nmnop\nqrst", 19), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "efgh", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "ijkl\nmnop\nqrst", 14), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "ijkl", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "mnop\nqrst", 9), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "mnop", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "qrst", 4), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "qrst", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "", 1), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, five_flush_not_ended, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "abcd\nefgh\nijkl\nmnop\nqrst", 24);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh\nijkl\nmnop\nqrst", 19), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "efgh", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "ijkl\nmnop\nqrst", 14), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "ijkl", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "mnop\nqrst", 9), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "mnop", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "qrst", 4), 0);
    cr_assert_eq(client_flush_line(&client, line), false);
    cr_assert_eq(memcmp(client.buffer, "qrst", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}

Test(client_flush_line, five_flush_not_ended_writes, .timeout = 5) {
    client_t client = {0};
    int pipefd[2];
    char line[CLIENT_BUFFER_SIZE + 1] = {0};

    cr_assert_eq(pipe(pipefd), 0);
    client.fd = pipefd[0];
    write(pipefd[1], "abcd\nefgh\nijkl", 14);
    write(pipefd[1], "\nmnop\nqrst", 10);
    cr_assert_eq(client_read_in_buffer(&client), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "abcd", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "efgh\nijkl\nmnop\nqrst", 19), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "efgh", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "ijkl\nmnop\nqrst", 14), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "ijkl", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "mnop\nqrst", 9), 0);
    cr_assert_eq(client_flush_line(&client, line), true);
    cr_assert_eq(memcmp(line, "mnop", 4), 0);
    cr_assert_eq(memcmp(client.buffer, "qrst", 4), 0);
    cr_assert_eq(client_flush_line(&client, line), false);
    cr_assert_eq(memcmp(client.buffer, "qrst", 4), 0);
    client_destroy(&client);
    close(pipefd[1]);
}
