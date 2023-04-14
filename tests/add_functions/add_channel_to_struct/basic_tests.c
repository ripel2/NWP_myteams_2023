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

Test(add_channel_to_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    char channel_uuid[37];
    char team_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andréas", channel_uuid, "Weirdo");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->name, "Andréas");
            cr_assert_str_eq(channel->description, "Weirdo");
            cr_assert_str_eq(channel->uuid, channel_uuid);
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_channel_to_struct, multiple_channel, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    char *name[3] = {"Andréas", "Louis", "Nugo"};
    int idx = 0;
    char team_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char *channel_uuid[3] = {"00000000-0000-0000-0000-000000000003",
        "00000000-0000-0000-0000-000000000004",
        "00000000-0000-0000-0000-000000000005"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andréas", channel_uuid[0], "Weirdo");
    add_channel_to_struct(team_uuid, "Louis", channel_uuid[1], "Weirdo");
    add_channel_to_struct(team_uuid, "Nugo", channel_uuid[2], "Weirdo");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->name, name[idx]);
            cr_assert_str_eq(channel->description, "Weirdo");
            cr_assert_str_eq(channel->uuid, channel_uuid[idx]);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_channel_to_struct, multiple_channel_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    channel_t *channel;
    char last_channel_uuid[37] = "00000000-0000-0000-0000-000000000000";
    int idx = 0;
    char channel_uuid[2][37];
    char team_uuid[37];

    channel_uuid[0][0] = '\0';
    channel_uuid[1][0] = '\0';
    team_uuid[0] = '\0';
    generate_uuid(channel_uuid[0]);
    generate_uuid(channel_uuid[1]);
    generate_uuid(team_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", team_uuid, "Description");
    add_channel_to_struct(team_uuid, "Andréas", channel_uuid[0], "Weirdo");
    add_channel_to_struct(team_uuid, "Andréas", channel_uuid[1], "Weirdo");
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->name, "Andréas");
            cr_assert_str_eq(channel->description, "Weirdo");
            cr_assert_str_eq(channel->uuid, channel_uuid[idx]);
            cr_assert_str_neq(channel->uuid, last_channel_uuid);
            last_channel_uuid[0] = '\0';
            strcat(last_channel_uuid, channel->uuid);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}
