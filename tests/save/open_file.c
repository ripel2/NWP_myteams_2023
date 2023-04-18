/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** basic_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "save.h"

Test(open_file, ok_open_read)
{
    FILE *fp = open_file("tests/save/tests_files/ok_open_read.my_teams", "r");

    cr_assert_not_null(fp);
    fclose(fp);
}

Test(open_file, ok_open_write)
{
    FILE *fp = open_file("tests/save/tests_files/ok_open_write.my_teams", "w");

    cr_assert_not_null(fp);
    fclose(fp);
}

Test(open_file, error_parameter)
{
    cr_redirect_stderr();
    FILE *fp = open_file(NULL, NULL);

    cr_assert_null(fp);
}

Test(open_file, error_file)
{
    cr_redirect_stderr();
    FILE *fp = open_file("tests/save/tests_files/error_file.my_teams", "r");

    cr_assert_not_null(fp);
    fclose(fp);
}
