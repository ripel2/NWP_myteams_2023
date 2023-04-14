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
    char team_uuid[37];
    char channel_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andros", channel_uuid, "TT");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->uuid);
            if (channel) {
                cr_assert_str_eq(channel->name, channel_got->name);
                cr_assert_str_eq(channel->description, channel_got->description);
                cr_assert_str_eq(channel->uuid, channel_got->uuid);
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
    char *channel_uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};
    char team_uuid[37];

    team_uuid[0] = '\0';
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andros", channel_uuid[0], "TT");
    add_channel_to_struct(team_uuid, "Lucaer", channel_uuid[1], "CC");
    add_channel_to_struct(team_uuid, "Louhihi", channel_uuid[2], "II");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->uuid);
            if (channel) {
                cr_assert_str_eq(channel->name, channel_got->name);
                cr_assert_str_eq(channel->description, channel_got->description);
                cr_assert_str_eq(channel->uuid, channel_got->uuid);
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
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char channel_uuid[2][37];
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";

    channel_uuid[0][0] = '\0';
    channel_uuid[1][0] = '\0';
    generate_uuid(channel_uuid[0]);
    generate_uuid(channel_uuid[1]);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Pugo", channel_uuid[0], "APE");
    add_channel_to_struct(team_uuid, "Pugo", channel_uuid[1], "EPA");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            channel_got = get_channel_from_struct(channel->uuid);
            if (channel) {
                cr_assert_str_eq(channel->name, channel_got->name);
                cr_assert_str_eq(channel->description, channel_got->description);
                cr_assert_str_eq(channel->uuid, channel_got->uuid);
                cr_assert_str_neq(channel->uuid, last_uuid);
                last_uuid[0] = '\0';
                strcpy(last_uuid, channel->uuid);
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
    char channel_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char team_uuid[37] = "00000000-0000-0000-0000-000000000000";


    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andros", channel_uuid, "TT");
    channel_got = get_channel_from_struct("00000000-0000-1111-0000-000000000000");
    cr_assert_null(channel_got);
    fini_dll(global->dll);
    free(global);
}
