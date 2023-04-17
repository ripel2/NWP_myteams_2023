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

Test(add_discussion_to_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    personal_discussion_t *discussion;
    user_t *user;
    data_t *user_data;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    add_user_to_struct(user_data);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data->uuid, user_data);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            cr_assert_str_eq("Lucas", discussion->user_data->name);
            cr_assert_str_eq(user_data->uuid, discussion->user_data->uuid);
            cr_assert_str_eq(discussion->uuid, "00000000-0000-0000-0000-000000000000");
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_discussion_to_struct, multiple_discussion, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    user_t *user;
    personal_discussion_t *discussion;
    data_t *user_data1;
    data_t *user_data2;
    data_t *user_data3;
    char *username[3] = {"Lucas", "Louis", "Andréas"};
    int idx = 0;
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
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data1->uuid, user_data1);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000001", user_data2->uuid, user_data2);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000002", user_data3->uuid, user_data3);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            cr_assert_str_eq(username[idx], discussion->user_data->name);
            cr_assert_str_eq(uuid[idx], discussion->user_data->uuid);
            cr_assert_str_eq(discussion->uuid, uuid[idx]);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}
