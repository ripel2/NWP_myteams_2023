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

Test(get_thread_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    thread_t *thread_got = NULL;
    data_t *thread_data = NULL;
    data_t *user_data = NULL;
    data_t *channel_data = NULL;
    data_t *team_data = NULL;
    char team_uuid[37];
    char channel_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    thread_data = init_data("Andros", "TT", "", channel_uuid);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                thread_got = get_thread_from_struct(thread->thread_data->uuid);
                if (thread) {
                    cr_assert_str_eq(thread->thread_data->name, thread_got->thread_data->name);
                    cr_assert_str_eq(thread->thread_data->body, thread_got->thread_data->body);
                    cr_assert_str_eq(thread->thread_data->uuid, thread_got->thread_data->uuid);
                }
            }
        }
    }
    
    free(global);
}

Test(get_thread_from_struct, multiple_thread, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    thread_t *thread_got = NULL;
    data_t *thread_data1 = NULL;
    data_t *thread_data2 = NULL;
    data_t *thread_data3 = NULL;
    data_t *user_data = NULL;
    data_t *channel_data = NULL;
    data_t *team_data = NULL;
    char *channel_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char team_uuid[37];

    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid[0]);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    thread_data1 = init_data("Andros", "", "TT", channel_uuid[0]);
    thread_data2 = init_data("Andros", "", "TT", channel_uuid[1]);
    thread_data3 = init_data("Andros", "", "TT", channel_uuid[2]);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid[0], user_data, thread_data1);
    add_thread_to_struct(channel_uuid[1], user_data, thread_data2);
    add_thread_to_struct(channel_uuid[2], user_data, thread_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                thread_got = get_thread_from_struct(thread->thread_data->uuid);
                if (thread) {
                    cr_assert_str_eq(thread->thread_data->name, thread_got->thread_data->name);
                    cr_assert_str_eq(thread->thread_data->body, thread_got->thread_data->body);
                    cr_assert_str_eq(thread->thread_data->uuid, thread_got->thread_data->uuid);
                }
            }
        }
    }
    
    free(global);
}

Test(get_thread_from_struct, multiple_thread_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    thread_t *thread_got = NULL;
    data_t *thread_data1 = NULL;
    data_t *thread_data2 = NULL;
    data_t *thread_data3 = NULL;
    data_t *user_data = NULL;
    data_t *channel_data = NULL;
    data_t *team_data = NULL;
    char *thread_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char last_uuid[37] = "00000000-0000-0000-5000-00000000a003";
    char channel_uuid[37];
    char team_uuid[37];

    channel_uuid[0] = '\0';
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    user_data = init_data("Lucas", "", "Description", "00000000-0000-0000-0000-000000000000");
    thread_data1 = init_data("Andros", "", "TT", thread_uuid[0]);
    thread_data2 = init_data("Andros", "", "TT", thread_uuid[1]);
    thread_data3 = init_data("Andros", "", "TT", thread_uuid[2]);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(thread_uuid[0], user_data, thread_data1);
    add_thread_to_struct(thread_uuid[1], user_data, thread_data2);
    add_thread_to_struct(thread_uuid[2], user_data, thread_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                thread_got = get_thread_from_struct(thread->thread_data->uuid);
                if (thread) {
                    cr_assert_str_eq(thread->thread_data->name, thread_got->thread_data->name);
                    cr_assert_str_eq(thread->thread_data->body, thread_got->thread_data->body);
                    cr_assert_str_neq(thread->thread_data->uuid, last_uuid);
                    last_uuid[0] = '\0';
                    strcat(last_uuid, thread->thread_data->uuid);
                }
            }
        }
    }
    
    free(global);
}

Test(get_thread_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    thread_t *thread_got = NULL;
    data_t *channel_data = NULL;
    data_t *team_data = NULL;

    char channel_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    thread_got = get_thread_from_struct("00000000-0000-1111-0000-000000000000");
    cr_assert_null(thread_got);
    
    free(global);
}
