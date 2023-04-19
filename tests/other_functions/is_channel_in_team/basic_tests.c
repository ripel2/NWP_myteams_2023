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

Test(is_channel_in_team, true_case, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
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
    channel_data = init_data("Andros", "TT", "", channel_uuid);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct(team_data);
    add_channel_to_struct(team_uuid, channel_data);
    cr_assert_eq(is_channel_in_team(channel_uuid, team_uuid), true);
    
    free(global);
}

Test(is_channel_in_team, false_case, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *team_data = NULL;
    char team_uuid[37];
    char channel_uuid[37];

    team_uuid[0] = '\0';
    channel_uuid[0] = '\0';
    generate_uuid(team_uuid);
    generate_uuid(channel_uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", team_uuid);
    add_team_to_struct(team_data);
    cr_assert_eq(is_channel_in_team(channel_uuid, team_uuid), false);
    
    free(global);
}
