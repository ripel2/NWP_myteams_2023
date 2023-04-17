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

Test(add_reply_to_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    data_t *channel_data;
    data_t *team_data;
    data_t *user_data;
    data_t *thread_data;
    data_t *reply_data;
    char channel_uuid[37];
    char team_uuid[37];
    char thread_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    thread_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    generate_uuid(thread_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    user_data = init_data("Lucas", "Description", "", "00000000-0000-0000-0000-000000000000");
    thread_data = init_data("Thread", "Je suis lucassssss", "", thread_uuid);
    reply_data = init_data("Reply", "Je suis lucassssss", "", "00000000-0000-0000-0000-000000000000");
    add_user_to_struct(user_data);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    add_reply_to_struct(thread_uuid, user_data, reply_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    cr_assert_str_eq(reply->user_data->name, "Lucas");
                    cr_assert_str_eq(reply->user_data->description, "Description");
                    cr_assert_str_eq(reply->user_data->body, "");
                    cr_assert_str_eq(reply->user_data->uuid, "00000000-0000-0000-0000-000000000000");
                    cr_assert_str_eq(reply->reply_data->name, "Reply");
                    cr_assert_str_eq(reply->reply_data->description, "Je suis lucassssss");
                    cr_assert_str_eq(reply->reply_data->body, "");
                    cr_assert_str_eq(reply->reply_data->uuid, "00000000-0000-0000-0000-000000000000");
                }
            }
        }
    }
    
    free(global);
}

Test(add_reply_to_struct, multiple_thread, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    data_t *channel_data;
    data_t *user_data;
    data_t *thread_data;
    data_t *reply_data1;
    data_t *reply_data2;
    data_t *reply_data3;
    data_t *team_data;

    char *name[3] = {"Andréas", "Louis", "Nugo"};
    int idx = 0;
    char team_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char channel_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char thread_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char reply_uuid[3][37] = {{"00000000-0000-0000-0000-000050000000"},
        {"00000000-0000-0000-0000-000005000000"},
        {"00000000-0000-0000-0000-000000500000"}};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    
    add_team_to_struct(team_data);
    channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    user_data = init_data("Lucas", "Description", "", "00000000-0000-0000-0000-000000000000");
    thread_data = init_data("Thread", "Je suis lucassssss", "", thread_uuid);
    reply_data1 = init_data(name[0], "Je suis lucassssss", "", reply_uuid[0]);
    reply_data2 = init_data(name[1], "Je suis lucassssss", "", reply_uuid[1]);
    reply_data3 = init_data(name[2], "Je suis lucassssss", "", reply_uuid[2]);
    add_user_to_struct(user_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    add_reply_to_struct(thread_uuid, user_data, reply_data1);
    add_reply_to_struct(thread_uuid, user_data, reply_data2);
    add_reply_to_struct(thread_uuid, user_data, reply_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    cr_assert_str_eq(reply->user_data->name, "Lucas");
                    cr_assert_str_eq(reply->user_data->description, "Description");
                    cr_assert_str_eq(reply->user_data->body, "");
                    cr_assert_str_eq(reply->user_data->uuid, "00000000-0000-0000-0000-000000000000");
                    cr_assert_str_eq(reply->reply_data->name, name[idx]);
                    cr_assert_str_eq(reply->reply_data->description, "Je suis lucassssss");
                    cr_assert_str_eq(reply->reply_data->body, "");
                    cr_assert_str_eq(reply->reply_data->uuid, reply_uuid[idx]);
                    idx++;
                }
            }
        }
    }
    
    free(global);
}

Test(add_reply_to_struct, multiple_reply_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    data_t *channel_data;
    data_t *user_data;
    data_t *thread_data;
    data_t *reply_data1;
    data_t *reply_data2;
    data_t *reply_data3;
    data_t *team_data;

    char *name[3] = {"Andréas", "Andréas", "Andréas"};
    int idx = 0;
    char team_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char channel_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char thread_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char reply_uuid[3][37] = {{"00000000-0000-0000-0000-000000000050"},
        {"00000000-0000-0000-0000-000000000001"},
        {"00000000-0000-0000-0000-000000000002"}};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    
    add_team_to_struct(team_data);
    channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    user_data = init_data("Lucas", "Description", "", "00000000-0000-0000-0000-000000000000");
    thread_data = init_data("Thread", "Je suis lucassssss", "", thread_uuid);
    reply_data1 = init_data(name[0], "Je suis lucassssss", "", reply_uuid[0]);
    reply_data2 = init_data(name[1], "Je suis lucassssss", "", reply_uuid[1]);
    reply_data3 = init_data(name[2], "Je suis lucassssss", "", reply_uuid[2]);
    add_user_to_struct(user_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    add_reply_to_struct(thread_uuid, user_data, reply_data1);
    add_reply_to_struct(thread_uuid, user_data, reply_data2);
    add_reply_to_struct(thread_uuid, user_data, reply_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                TAILQ_FOREACH(reply, &thread->replies, entries) {
                    cr_assert_str_eq(reply->user_data->name, "Lucas");
                    cr_assert_str_eq(reply->user_data->description, "Description");
                    cr_assert_str_eq(reply->user_data->body, "");
                    cr_assert_str_eq(reply->user_data->uuid, "00000000-0000-0000-0000-000000000000");
                    cr_assert_str_eq(reply->reply_data->name, name[idx]);
                    cr_assert_str_eq(reply->reply_data->description, "Je suis lucassssss");
                    cr_assert_str_eq(reply->reply_data->body, "");
                    cr_assert_str_eq(reply->reply_data->uuid, reply_uuid[idx]);
                    idx++;
                }
            }
        }
    }
    
    free(global);
}