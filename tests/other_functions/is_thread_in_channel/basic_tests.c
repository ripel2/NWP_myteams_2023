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

Test(is_thread_in_channel, true_case, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    data_t *thread_data;
    data_t *user_data;
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
    thread_data = init_data("Andros", "TT", "", channel_uuid);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    cr_assert_eq(is_thread_in_channel(thread_data->uuid, channel_uuid), true);
    fini_dll(global->dll);
    free(global);
}

Test(is_thread_in_channel, false_case, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    global->dll = init_dll();
    data_t *thread_data;
    data_t *user_data;
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
    thread_data = init_data("Andros", "TT", "", channel_uuid);
    user_data = init_data("Lucas", "", "Description", team_uuid);
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_channel_to_struct(team_uuid, channel_data);
    add_user_to_struct(user_data);
    add_thread_to_struct(channel_uuid, user_data, thread_data);
    cr_assert_eq(is_thread_in_channel(thread_data->uuid, "888"), false);
    fini_dll(global->dll);
    free(global);
}
