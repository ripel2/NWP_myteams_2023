/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** split_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "shared.h"

Test(split_string_fixed_array, basic_1) {
    char *str = strdup("Hello World");
    char *args[3] = {NULL};

    split_string_fixed_array(str, args, 3);
    cr_assert_str_eq(args[0], "Hello");
    cr_assert_str_eq(args[1], "World");
    cr_assert_null(args[2]);
    free(str);
}

Test(split_string_fixed_array, basic_2) {
    char *str = strdup("Hello World");
    char *args[2] = {NULL};

    split_string_fixed_array(str, args, 2);
    cr_assert_str_eq(args[0], "Hello");
    cr_assert_null(args[1]);
    free(str);
}

Test(split_string_fixed_array, basic_3) {
    char *str = strdup("Hello World");
    char *args[1] = {NULL};

    split_string_fixed_array(str, args, 1);
    cr_assert_null(args[0]);
    free(str);
}

Test(split_string_fixed_array, double_quotes_1) {
    char *str = strdup("Hello \"World\"");
    char *args[3] = {NULL};

    split_string_fixed_array(str, args, 3);
    cr_assert_str_eq(args[0], "Hello");
    cr_assert_str_eq(args[1], "\"World\"");
    cr_assert_null(args[2]);
    free(str);
}

Test(split_string_fixed_array, double_quotes_2) {
    char *str = strdup("Hello \"World\"");
    char *args[2] = {NULL};

    split_string_fixed_array(str, args, 2);
    cr_assert_str_eq(args[0], "Hello");
    cr_assert_null(args[1]);
    free(str);
}

Test(split_string_fixed_array, double_quotes_3) {
    char *str = strdup("Hello \"World\"");
    char *args[1] = {NULL};

    split_string_fixed_array(str, args, 1);
    cr_assert_null(args[0]);
    free(str);
}

Test(split_string_fixed_array, error_1) {
    char *str = strdup("");
    char *args[4] = {NULL};

    split_string_fixed_array(str, args, 4);
    cr_assert_null(args[0]);
    free(str);
}

Test(split_string_fixed_array, error_2) {
    char *str = strdup("test");
    char *args[1] = {NULL};

    split_string_fixed_array(str, args, 1);
    cr_assert_null(args[0]);
    free(str);
}

Test(split_string_fixed_array, use_case_1) {
    char *str = strdup("/login \"Andrip dreas\"");
    char *args[3] = {NULL};

    split_string_fixed_array(str, args, 3);
    cr_assert_str_eq(args[0], "/login");
    cr_assert_str_eq(args[1], "\"Andrip dreas\"");
    cr_assert_null(args[2]);
    free(str);
}

Test(split_string_fixed_array, use_case_2) {
    char *str = strdup("/use \"fake-uuid-1\" \"fake-uuid-2\" \"fake-uuid-3\"");
    char *args[5] = {NULL};

    split_string_fixed_array(str, args, 5);
    cr_assert_str_eq(args[0], "/use");
    cr_assert_str_eq(args[1], "\"fake-uuid-1\"");
    cr_assert_str_eq(args[2], "\"fake-uuid-2\"");
    cr_assert_str_eq(args[3], "\"fake-uuid-3\"");
    cr_assert_null(args[4]);
    free(str);
}

Test(split_string_fixed_array, use_case_3) {
    char *str = strdup("USE \"fake-uuid-1\" \"fake-uuid-2\" \"fake-uuid-3\"");
    char *args[5] = {NULL};

    split_string_fixed_array(str, args, 5);
    cr_assert_str_eq(args[0], "USE");
    cr_assert_str_eq(args[1], "\"fake-uuid-1\"");
    cr_assert_str_eq(args[2], "\"fake-uuid-2\"");
    cr_assert_str_eq(args[3], "\"fake-uuid-3\"");
    cr_assert_null(args[4]);
    free(str);
}

Test(split_string_fixed_array, use_case_4) {
    char *str = strdup("1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f team1 description");
    char *args[4] = {NULL};

    split_string_fixed_array(str, args, 4);
    cr_assert_str_eq(args[0], "1e6b0b0a-5b9f-4b3b-8c9a-8d2b2c3d4e5f");
    cr_assert_str_eq(args[1], "team1");
    cr_assert_str_eq(args[2], "description");
    cr_assert_null(args[3]);
    free(str);
}

Test(split_string_fixed_array, spaces_1) {
    char *str = strdup("coucou      ");
    char *args[2] = {NULL};

    split_string_fixed_array(str, args, 2);
    cr_assert_str_eq(args[0], "coucou");
    cr_assert_null(args[1]);
}

Test(split_string_fixed_array, spaces_2) {
    char *str = strdup("    coucou");
    char *args[2] = {NULL};

    split_string_fixed_array(str, args, 2);
    cr_assert_str_eq(args[0], "coucou");
    cr_assert_null(args[1]);
}

Test(split_string_fixed_array, spaces_3) {
    char *str = strdup("    coucou      ");
    char *args[2] = {NULL};

    split_string_fixed_array(str, args, 2);
    cr_assert_str_eq(args[0], "coucou");
    cr_assert_null(args[1]);
}
