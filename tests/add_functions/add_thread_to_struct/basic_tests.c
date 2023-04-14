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

Test(add_thread_to_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    data_t *channel_data;
    data_t *team_data;
    data_t *user_data;
    data_t *thread_data;
    char channel_uuid[37];
    char team_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    user_data = init_data("Lucas", "Description", "", "00000000-0000-0000-0000-000000000000");
    thread_data = init_data("Thread", "", "Je suis lucassssss", "00000000-0000-0000-0000-000000000000");
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                cr_assert_str_eq(thread->thread_data->name, "Thread");
                cr_assert_str_eq(thread->thread_data->body, "Je suis lucassssss");
                cr_assert_str_eq(thread->thread_data->uuid, "00000000-0000-0000-0000-000000000000");
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_thread_to_struct, multiple_thread, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    data_t *channel_data;
    data_t *user_data;
    data_t *thread_data1;
    data_t *thread_data2;
    data_t *thread_data3;
    data_t *team_data;

    char *name[3] = {"Andréas", "Louis", "Nugo"};
    int idx = 0;
    char team_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char channel_uuid[37] = {"00000000-0000-0000-0000-000000000001"};
    char *thread_uuid[3] = {"00000000-0000-0000-0000-000000000003",
        "00000000-0000-0000-0000-000000000004",
        "00000000-0000-0000-0000-000000000005"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct(team_data);
    channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    user_data = init_data("Lucas", "Description", "", "00000000-0000-0000-0000-000000000000");
    thread_data1 = init_data(name[0], "", "Je suis lucassssss", thread_uuid[0]);
    thread_data2 = init_data(name[1], "", "Je suis lucassssss", thread_uuid[1]);
    thread_data3 = init_data(name[2], "", "Je suis lucassssss", thread_uuid[2]);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data1);
    add_thread_to_struct(channel_uuid, user_data, thread_data2);
    add_thread_to_struct(channel_uuid, user_data, thread_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                cr_assert_str_eq(thread->thread_data->name, name[idx]);
                cr_assert_str_eq(thread->thread_data->body, "Je suis lucassssss");
                cr_assert_str_eq(thread->thread_data->uuid, thread_uuid[idx]);
                idx++;
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_thread_to_struct, multiple_thread_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    thread_t *thread;
    team_t *team;
    channel_t *channel;
    data_t *Andréas_channel_data;
    data_t *Lucas_team_data;
    data_t *user_data;
    data_t *thread_data1;
    data_t *thread_data2;
    char last_thread_uuid[37] = "00000000-0000-0000-0000-000000000000";
    int idx = 0;
    char channel_uuid[37] = {"00000000-0000-0000-0000-000000000001"};
    char thread_uuid[2][37];
    char team_uuid[37];

    thread_uuid[0][0] = '\0';
    thread_uuid[1][0] = '\0';
    team_uuid[0] = '\0';
    generate_uuid(thread_uuid[0]);
    generate_uuid(thread_uuid[1]);
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    Andréas_channel_data = init_data("Andréas", "Weirdo", "", channel_uuid);
    Lucas_team_data = init_data("Lucas", "Description", "", team_uuid);
    user_data = init_data("Lucas", "", "", "00000000-0000-0000-0000-000000000000");
    thread_data1 = init_data("Andréas", "", "Je suis lucassssss", thread_uuid[0]);
    thread_data2 = init_data("Andréas", "", "Je suis lucassssss", thread_uuid[1]);
    add_user_to_struct(user_data);
    add_team_to_struct(Lucas_team_data);
    add_channel_to_struct(team_uuid, Andréas_channel_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data1);
    add_thread_to_struct(channel_uuid, user_data, thread_data2);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            TAILQ_FOREACH(thread, &channel->threads, entries) {
                cr_assert_str_eq(thread->thread_data->name, "Andréas");
                cr_assert_str_eq(thread->thread_data->body, "Je suis lucassssss");
                cr_assert_str_eq(thread->thread_data->uuid, thread_uuid[idx]);
                cr_assert_str_neq(thread->thread_data->uuid, last_thread_uuid);
                last_thread_uuid[0] = '\0';
                strcat(last_thread_uuid, thread->thread_data->uuid);
                idx++;
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}
