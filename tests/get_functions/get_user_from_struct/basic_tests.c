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
#include "loader.h"

dlloader_t *init_dll(void);
void fini_dll(dlloader_t *dll);
void redirect_all_stderr(void);

Test(get_user_from_struct, basic_test, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;
    user_t *user_got;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        user_got = get_user_from_struct(user->uuid, global);
        if (user) {
            cr_assert_str_eq(user->username, user_got->username);
            cr_assert_eq(user->is_logged, user_got->is_logged);
        }
    }
    fini_dll(dll);
    free(global);
}

Test(get_user_from_struct, multiple_user, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;
    user_t *user_got;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    add_user_to_struct("Louis", dll, global);
    add_user_to_struct("Andréas", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        user_got = get_user_from_struct(user->uuid, global);
        if (user) {
            cr_assert_str_eq(user->username, user_got->username);
            cr_assert_eq(user->is_logged, user_got->is_logged);
        }
    }
    fini_dll(dll);
    free(global);
}

Test(get_user_from_struct, multiple_user_with_same_name, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;
    user_t *user_got;
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    add_user_to_struct("Louis", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        if (user) {
            user_got = get_user_from_struct(user->uuid, global);
            if (user) {
                cr_assert_str_eq(user->username, user_got->username);
                cr_assert_eq(user->is_logged, user_got->is_logged);
                cr_assert_str_neq(user->uuid, last_uuid);
                last_uuid[0] = '\0';
                strcat(last_uuid, user->uuid);
            }
        }
    }
    fini_dll(dll);
    free(global);
}

Test(get_user_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user_got;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    add_user_to_struct("Louis", dll, global);
    user_got = get_user_from_struct("00000000-0000-0000-0000-000000000000", global);
    cr_assert_null(user_got);
    fini_dll(dll);
    free(global);
}
