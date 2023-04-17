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




void redirect_all_stderr(void);

Test(get_discussion_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data;
    user_t *user;
    personal_discussion_t *discussion;
    personal_discussion_t *discussion_got;
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
            discussion_got = get_personnal_discussion_from_struct(discussion->uuid);
            cr_assert_not_null(discussion_got);
            cr_assert_str_eq(discussion->uuid, discussion_got->uuid);
            cr_assert_str_eq(discussion->user_data->uuid, discussion_got->user_data->uuid);
            cr_assert_str_eq(discussion->user_data->name, discussion_got->user_data->name);
        }
    }
    
    free(global);
}

Test(get_discussion_from_struct, multiple_discussion, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    data_t *user_data3;
    user_t *user;
    personal_discussion_t *discussion;
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
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data1->uuid, user_data1);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000001", user_data2->uuid, user_data2);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000002", user_data3->uuid, user_data3);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            user_got = get_user_from_struct(discussion->user_data->uuid);
            cr_assert_not_null(user_got);
            cr_assert_str_eq(user_got->user_data->uuid, discussion->user_data->uuid);
            cr_assert_str_eq(user_got->user_data->name, discussion->user_data->name);
        }
    }
    
    free(global);
}

Test(get_discussion_from_struct, multiple_user_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    user_t *user;
    personal_discussion_t *discussion;
    personal_discussion_t *discussion_got;
    char last_uuid[37] = "";
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
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data1->uuid, user_data1);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000001", user_data2->uuid, user_data2);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            discussion_got = get_personnal_discussion_from_struct(discussion->uuid);
            cr_assert_not_null(discussion_got);
            cr_assert_str_eq(discussion->uuid, discussion_got->uuid);
            cr_assert_str_eq(discussion->user_data->uuid, discussion_got->user_data->uuid);
            cr_assert_str_eq(discussion->user_data->name, discussion_got->user_data->name);
            cr_assert_str_neq(last_uuid, discussion->uuid);
            strcat(last_uuid, discussion->uuid);
        }
    }
    
    free(global);
}

Test(get_discussion_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *user_data1;
    data_t *user_data2;
    personal_discussion_t *discussion_got;
    char *uuid[2] = {"00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data1 = init_data("Lucas", "", "", uuid[0]);
    user_data2 = init_data("Louis", "", "", uuid[1]);
    add_user_to_struct(user_data1);
    add_user_to_struct(user_data2);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000006000", user_data1->uuid, user_data1);
    discussion_got = get_personnal_discussion_from_struct("00000000-0000-0000-0000-000000000000");
    cr_assert_null(discussion_got);
    
    free(global);
}
