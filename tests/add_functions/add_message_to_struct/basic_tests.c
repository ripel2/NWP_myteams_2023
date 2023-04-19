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

Test(add_message_to_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    personal_discussion_t *discussion = NULL;
    message_t *message;
    user_t *user = NULL;
    data_t *user_data = NULL;
    data_t *message_data = NULL;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    message_data = init_data("Lucas", "", "hello", uuid);
    add_user_to_struct(user_data);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data->uuid, user_data);
    add_message_to_struct(user_data, user_data, message_data);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            TAILQ_FOREACH(message, &discussion->messages, entries) {
                cr_assert_not_null(message);
                cr_assert_str_eq(message->user_data->uuid, user_data->uuid);
                cr_assert_str_eq(message->user_data->name, user_data->name);
                cr_assert_str_eq(message->message_data->body, "Hello");
            }
        }
    }
    
    free(global);
}

Test(add_message_to_struct, multiple_message, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    user_t *user = NULL;
    personal_discussion_t *discussion = NULL;
    message_t *message;
    data_t *user_data1 = NULL;
    data_t *user_data2 = NULL;
    data_t *user_data3 = NULL;
    data_t *message_data1 = NULL;
    data_t *message_data2 = NULL;
    data_t *message_data3 = NULL;
    char *username[3] = {"Lucas", "Louis", "Andréas"};
    int idx = 0;
    char *uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char *message_body[3] = {"Hello1", "Hello2", "Hello3"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data1 = init_data("Lucas", "", "", uuid[0]);
    user_data2 = init_data("Louis", "", "", uuid[1]);
    user_data3 = init_data("Andréas", "", "", uuid[2]);
    message_data1 = init_data("Lucas", "", message_body[0], uuid[0]);
    message_data2 = init_data("Louis", "", message_body[1], uuid[1]);
    message_data3 = init_data("Andréas", "", message_body[2], uuid[2]);
    add_user_to_struct(user_data1);
    add_user_to_struct(user_data2);
    add_user_to_struct(user_data3);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", user_data1->uuid, user_data1);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000001", user_data2->uuid, user_data2);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000002", user_data3->uuid, user_data3);
    add_message_to_struct(user_data1, user_data1, message_data1);
    add_message_to_struct(user_data2, user_data2, message_data2);
    add_message_to_struct(user_data3, user_data3, message_data3);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            TAILQ_FOREACH(message, &discussion->messages, entries) {
                cr_assert_not_null(message);
                cr_assert_str_eq(message->user_data->uuid, uuid[idx]);
                cr_assert_str_eq(message->user_data->name, username[idx]);
                cr_assert_str_eq(message->message_data->body, message_body[idx]);
                idx++;
            }
        }
    }
    
    free(global);
}

Test(add_message_to_struct, no_discussion, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    personal_discussion_t *discussion = NULL;
    message_t *message;
    user_t *user = NULL;
    data_t *user_data = NULL;
    data_t *message_data = NULL;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    message_data = init_data("Lucas", "", "hello", uuid);
    add_user_to_struct(user_data);
    cr_assert_eq(add_message_to_struct(user_data, user_data, message_data), 84);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(discussion, &user->discussions, entries) {
            TAILQ_FOREACH(message, &discussion->messages, entries) {
                cr_assert_null(message);
            }
        }
    }
    
    free(global);
}
