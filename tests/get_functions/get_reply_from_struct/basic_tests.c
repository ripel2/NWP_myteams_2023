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

Test(get_reply_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    reply_t *reply_got;
    data_t *thread_data;
    data_t *user_data;
    data_t *channel_data;
    data_t *team_data;
    data_t *reply_data;
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
    reply_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    add_reply_to_struct(channel_uuid, user_data, reply_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    reply_got = get_reply_from_struct(reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->uuid,
                        reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->name, reply_got->reply_data->name);
                    cr_assert_str_eq(reply_got->reply_data->description,
                        reply_got->reply_data->description);
                    cr_assert_str_eq(reply_got->reply_data->body, reply_got->reply_data->body);
                }
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_reply_from_struct, multiple_reply, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    reply_t *reply_got;
    data_t *thread_data;
    data_t *reply_data1;
    data_t *reply_data2;
    data_t *reply_data3;
    data_t *user_data;
    data_t *channel_data;
    data_t *team_data;
    char *reply_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char team_uuid[37];
    char thread_uuid[37] = "00000000-0000-0000-0000-000000000000";

    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", team_uuid);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    thread_data = init_data("Andros", "TT", "", thread_uuid);
    reply_data1 = init_data("Lucas", "Description", "", reply_uuid[0]);
    reply_data2 = init_data("Lucas", "Description", "", reply_uuid[1]);
    reply_data3 = init_data("Lucas", "Description", "", reply_uuid[2]);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(team_uuid, user_data, thread_data);
    add_reply_to_struct(thread_uuid, user_data, reply_data1);
    add_reply_to_struct(thread_uuid, user_data, reply_data2);
    add_reply_to_struct(thread_uuid, user_data, reply_data3);

    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    reply_got = get_reply_from_struct(reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->uuid,
                        reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->name, reply_got->reply_data->name);
                    cr_assert_str_eq(reply_got->reply_data->description,
                        reply_got->reply_data->description);
                    cr_assert_str_eq(reply_got->reply_data->body, reply_got->reply_data->body);
                }
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_reply_from_struct, multiple_reply_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    reply_t *reply_got;
    data_t *thread_data;
    data_t *reply_data1;
    data_t *reply_data2;
    data_t *reply_data3;
    data_t *user_data;
    data_t *channel_data;
    data_t *team_data;
    char *reply_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char team_uuid[37];
    char thread_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char last_uuid[37] = "00000000-0000-0000-0000-000000000001";

    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", team_uuid);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    thread_data = init_data("Andros", "TT", "", thread_uuid);
    reply_data1 = init_data("Lucas", "Description", "", reply_uuid[0]);
    reply_data2 = init_data("Lucas", "Description", "", reply_uuid[1]);
    reply_data3 = init_data("Lucas", "Description", "", reply_uuid[2]);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(team_uuid, user_data, thread_data);
    add_reply_to_struct(thread_uuid, user_data, reply_data1);
    add_reply_to_struct(thread_uuid, user_data, reply_data2);
    add_reply_to_struct(thread_uuid, user_data, reply_data3);

    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    reply_got = get_reply_from_struct(reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->uuid,
                        reply->reply_data->uuid);
                    cr_assert_str_eq(reply_got->reply_data->name, reply_got->reply_data->name);
                    cr_assert_str_eq(reply_got->reply_data->description,
                        reply_got->reply_data->description);
                    cr_assert_str_eq(reply_got->reply_data->body, reply_got->reply_data->body);
                    cr_assert_str_neq(reply_got->reply_data->uuid, last_uuid);
                    strcat(last_uuid, reply_got->reply_data->uuid);
                }
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_reply_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    reply_t *reply_got;
    data_t *thread_data;
    data_t *channel_data;
    data_t *team_data;
    data_t *user_data;

    char channel_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    thread_data = init_data("Andros", "TT", "", "00000000-0000-1111-0000-000000000000");
    user_data = init_data("Lucas", "", "Description", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(team_uuid, user_data, thread_data);
    reply_got = get_reply_from_struct("00000000-0000-0000-0000-000000000000");
    cr_assert_null(reply_got);
    fini_dll(global->dll);
    free(global);
}
