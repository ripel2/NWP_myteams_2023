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
    data_t *channel_data;
    data_t *team_data;
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
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->channel_data->name, "Andréas");
            cr_assert_str_eq(channel->channel_data->description, "Weirdo");
            cr_assert_str_eq(channel->channel_data->uuid, channel_uuid);
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
    data_t *andreas_channel_data;
    data_t *louis_channel_data;
    data_t *nugo_channel_data;
    data_t *team_data;
    char *name[3] = {"Andréas", "Louis", "Nugo"};
    int idx = 0;
    char team_uuid[37] = {"00000000-0000-0000-0000-000000000000"};
    char *channel_uuid[3] = {"00000000-0000-0000-0000-000000000003",
        "00000000-0000-0000-0000-000000000004",
        "00000000-0000-0000-0000-000000000005"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    andreas_channel_data = init_data("Andréas", "Weirdo", "", channel_uuid[0]);
    louis_channel_data = init_data("Louis", "Weirdo", "", channel_uuid[1]);
    nugo_channel_data = init_data("Nugo", "Weirdo", "", channel_uuid[2]);
    add_channel_to_struct(team_uuid, andreas_channel_data);
    add_channel_to_struct(team_uuid, louis_channel_data);
    add_channel_to_struct(team_uuid, nugo_channel_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->channel_data->name, name[idx]);
            cr_assert_str_eq(channel->channel_data->description, "Weirdo");
            cr_assert_str_eq(channel->channel_data->uuid, channel_uuid[idx]);
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
    data_t *Andréas_channel_data;
    data_t *Andréas_channel_data2;
    data_t *Lucas_team_data;
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
    Andréas_channel_data = init_data("Andréas", "Weirdo", "", channel_uuid[0]);
    Andréas_channel_data2 = init_data("Andréas", "Weirdo", "", channel_uuid[1]);
    Lucas_team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", Lucas_team_data);
    add_channel_to_struct(team_uuid, Andréas_channel_data);
    add_channel_to_struct(team_uuid, Andréas_channel_data2);
    TAILQ_FOREACH(team, &global->teams, entries) {
        TAILQ_FOREACH(channel, &team->channels, entries) {
            cr_assert_str_eq(channel->channel_data->name, "Andréas");
            cr_assert_str_eq(channel->channel_data->description, "Weirdo");
            cr_assert_str_eq(channel->channel_data->uuid, channel_uuid[idx]);
            cr_assert_str_neq(channel->channel_data->uuid, last_channel_uuid);
            last_channel_uuid[0] = '\0';
            strcat(last_channel_uuid, channel->channel_data->uuid);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}
