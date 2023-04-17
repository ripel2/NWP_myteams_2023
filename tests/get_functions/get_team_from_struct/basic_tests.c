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

Test(get_team_from_struct, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    team_t *team_got;
    data_t *team_data;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", uuid);
    add_team_to_struct(team_data);
    TAILQ_FOREACH(team, &global->teams, entries) {
        team_got = get_team_from_struct(team->team_data->uuid);
        if (team) {
            cr_assert_str_eq(team->team_data->name, team_got->team_data->name);
            cr_assert_str_eq(team->team_data->description, team_got->team_data->description);
            cr_assert_str_eq(team->team_data->uuid, team_got->team_data->uuid);
        }
    }
    
    free(global);
}

Test(get_team_from_struct, multiple_team, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    team_t *team_got;
    data_t *team_data1;
    data_t *team_data2;
    data_t *team_data3;
    char *uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data1 = init_data("Lucas", "Description", "", uuid[0]);
    team_data2 = init_data("Louis", "Description", "", uuid[1]);
    team_data3 = init_data("Andréas", "Description", "", uuid[2]);
    add_team_to_struct(team_data1);
    add_team_to_struct(team_data2);
    add_team_to_struct(team_data3);
    TAILQ_FOREACH(team, &global->teams, entries) {
        team_got = get_team_from_struct(team->team_data->uuid);
        if (team) {
            cr_assert_str_eq(team->team_data->name, team_got->team_data->name);
            cr_assert_str_eq(team->team_data->description, team_got->team_data->description);
            cr_assert_str_eq(team->team_data->uuid, team_got->team_data->uuid);
        }
    }
    
    free(global);
}

Test(get_team_from_struct, multiple_team_with_same_name, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    team_t *team;
    team_t *team_got;
    data_t *team_data1;
    data_t *team_data2;
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    char uuid[2][37];

    uuid[0][0] = '\0';
    uuid[1][0] = '\0';
    generate_uuid(uuid[0]);
    generate_uuid(uuid[1]);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data1 = init_data("Lucas", "Description", "", uuid[0]);
    team_data2 = init_data("Lucas", "Description", "", uuid[1]);
    add_team_to_struct(team_data1);
    add_team_to_struct(team_data2);
    TAILQ_FOREACH(team, &global->teams, entries) {
        if (team) {
            team_got = get_team_from_struct(team->team_data->uuid);
            if (team) {
                cr_assert_str_eq(team->team_data->name, team_got->team_data->name);
                cr_assert_str_eq(team->team_data->description, team_got->team_data->description);
                cr_assert_str_eq(team->team_data->uuid, team_got->team_data->uuid);
                cr_assert_str_neq(team->team_data->uuid, last_uuid);
                last_uuid[0] = '\0';
                strcat(last_uuid, team->team_data->uuid);
            }
        }
    }
    
    free(global);
}

Test(get_team_from_struct, bad_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    data_t *team_data;
    data_t *team_data2;
    team_t *team_got;
    char *uuid[2] = {"00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    team_data = init_data("Lucas", "Description", "", uuid[0]);
    team_data2 = init_data("Louis", "Description", "", uuid[1]);
    add_team_to_struct(team_data);
    add_team_to_struct(team_data2);
    team_got = get_team_from_struct("00000000-0000-0000-0000-000000000000");
    cr_assert_null(team_got);
    
    free(global);
}
