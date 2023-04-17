/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** basic_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include "data_struct_functions.h"
#include "data.h"


dlloader_t *init_dll(void);
void fini_dll(dlloader_t *dll);
void redirect_all_stderr(void);

Test(get_user_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data;
    user_t *user;
    user_t *user_got;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    add_user_to_struct(user_data);
    TAILQ_FOREACH(user, &global->users, entries) {
        user_got = get_user_from_struct(user->user_data->uuid);
        if (user) {
            cr_assert_str_eq(user->user_data->name, user_got->user_data->name);
            cr_assert_eq(user->is_logged, user_got->is_logged);
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_user_from_struct, multiple_user, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    data_t *user_data3;
    user_t *user;
    user_t *user_got;
    char *uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data1 = init_data("Lucas", "", "", uuid[0]);
    user_data2 = init_data("Louis", "", "", uuid[1]);
    user_data3 = init_data("Andréas", "", "", uuid[2]);
    add_user_to_struct(user_data1);
    add_user_to_struct(user_data2);
    add_user_to_struct(user_data3);
    TAILQ_FOREACH(user, &global->users, entries) {
        user_got = get_user_from_struct(user->user_data->uuid);
        if (user) {
            cr_assert_str_eq(user->user_data->name, user_got->user_data->name);
            cr_assert_eq(user->is_logged, user_got->is_logged);
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_user_from_struct, multiple_user_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    user_t *user;
    user_t *user_got;
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char uuid[2][37];

    uuid[0][0] = '\0';
    uuid[1][0] = '\0';
    generate_uuid(uuid[0]);
    generate_uuid(uuid[1]);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data1 = init_data("Lucas", "", "", uuid[0]);
    user_data2 = init_data("Lucas", "", "", uuid[1]);
    add_user_to_struct(user_data1);
    add_user_to_struct(user_data2);
    TAILQ_FOREACH(user, &global->users, entries) {
        if (user) {
            user_got = get_user_from_struct(user->user_data->uuid);
            if (user) {
                cr_assert_str_eq(user->user_data->name, user_got->user_data->name);
                cr_assert_eq(user->is_logged, user_got->is_logged);
                cr_assert_str_neq(user->user_data->uuid, last_uuid);
                last_uuid[0] = '\0';
                strcat(last_uuid, user->user_data->uuid);
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_user_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    user_t *user_got;
    char *uuid[2] = {"00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data1 = init_data("Lucas", "", "", uuid[0]);
    user_data2 = init_data("Louis", "", "", uuid[1]);
    add_user_to_struct(user_data1);
    add_user_to_struct(user_data2);
    user_got = get_user_from_struct("00000000-0000-0000-0000-000000000000");
    cr_assert_null(user_got);
    fini_dll(global->dll);
    free(global);
}
