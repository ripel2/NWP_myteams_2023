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

Test(add_user_to_struct, basic_test, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        cr_assert_str_eq("Lucas", user->username);
        cr_assert_eq(user->is_logged, false);
    }
    fini_dll(dll);
    free(global);
}

Test(add_user_to_struct, multiple_user, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;
    char *username[3] = {"Lucas", "Louis", "Andréas"};
    int idx = 0;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    add_user_to_struct("Louis", dll, global);
    add_user_to_struct("Andréas", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        cr_assert_str_eq(username[idx], user->username);
        cr_assert_eq(user->is_logged, false);
        idx++;
    }
    fini_dll(dll);
    free(global);
}

Test(add_user_to_struct, multiple_user_with_same_name, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    dlloader_t *dll = init_dll();
    user_t *user;
    char *username[2] = {"Lucas", "Louis"};
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    int idx = 0;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_user_to_struct("Lucas", dll, global);
    add_user_to_struct("Louis", dll, global);
    TAILQ_FOREACH(user, &global->users, entries) {
        if (user) {
            cr_assert_str_eq(username[idx], user->username);
            cr_assert_str_neq(last_uuid, user->uuid);
            cr_assert_eq(user->is_logged, false);
            last_uuid[0] = '\0';
            strcat(last_uuid, user->uuid);
            idx++;
        }
    }
    fini_dll(dll);
    free(global);
}
