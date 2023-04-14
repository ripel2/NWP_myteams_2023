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

Test(get_channel_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    channel_t *channel_got;
    data_t *channel_data;
    data_t *team_data;
    char team_uuid[37];
    char channel_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->channel_data->uuid);
            if (channel) {
                cr_assert_str_eq(channel->channel_data->name, channel_got->channel_data->name);
                cr_assert_str_eq(channel->channel_data->description, channel_got->channel_data->description);
                cr_assert_str_eq(channel->channel_data->uuid, channel_got->channel_data->uuid);
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_channel_from_struct, multiple_channel, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    channel_t *channel_got;
    data_t *channel_data1;
    data_t *channel_data2;
    data_t *channel_data3;
    data_t *team_data;
    char *channel_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char team_uuid[37];

    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data1 = init_data("Andros", "TT", "", channel_uuid[0]);
    channel_data2 = init_data("Lucaer", "CC", "", channel_uuid[1]);
    channel_data3 = init_data("Louhihi", "II", "", channel_uuid[2]);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data1);
    add_channel_to_struct(team_uuid, channel_data2);
    add_channel_to_struct(team_uuid, channel_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->channel_data->uuid);
            if (channel) {
                cr_assert_str_eq(channel->channel_data->name, channel_got->channel_data->name);
                cr_assert_str_eq(channel->channel_data->description, channel_got->channel_data->description);
                cr_assert_str_eq(channel->channel_data->uuid, channel_got->channel_data->uuid);
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_channel_from_struct, multiple_channel_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    channel_t *channel_got;
    data_t *channel_data1;
    data_t *channel_data2;
    data_t *team_data;
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char channel_uuid[2][37];
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";

    channel_uuid[0][0] = '\0';
    channel_uuid[1][0] = '\0';
    generate_uuid(channel_uuid[0]);
    generate_uuid(channel_uuid[1]);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data1 = init_data("Andros", "TT", "", channel_uuid[0]);
    channel_data2 = init_data("Andros", "CC", "", channel_uuid[1]);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data1);
    add_channel_to_struct(team_uuid, channel_data2);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->channel_data->uuid);
            if (channel) {
                cr_assert_str_eq(channel->channel_data->name, channel_got->channel_data->name);
                cr_assert_str_eq(channel->channel_data->description, channel_got->channel_data->description);
                cr_assert_str_eq(channel->channel_data->uuid, channel_got->channel_data->uuid);
                cr_assert_str_neq(channel->channel_data->uuid, last_uuid);
                last_uuid[0] = '\0';
                strcpy(last_uuid, channel->channel_data->uuid);
            }
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(get_channel_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    channel_t *channel_got;
    data_t *channel_data;
    data_t *team_data;
    char channel_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    channel_got = get_channel_from_struct("00000000-0000-1111-0000-000000000000");
    cr_assert_null(channel_got);
    fini_dll(global->dll);
    free(global);
}
