/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** basic_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "save.h"
#include "data_struct_functions.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void init_global(void)
{
    if (global)
        free(global);
    global = malloc(sizeof(global_t));
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    redirect_all_std();
}

Test(read, read_simple, .init=init_global)
{
    char *names[] = {"Niska", "PNL", "Franky Vincent"};
    char *description[] = {"Rappeur", "Rappeur", "Zoukeur"};
    char **uuids = malloc(sizeof(char *) * 3);
    char **teams_uuids = malloc(sizeof(char *) * 3);
    char *teams_names[] = {"Team1", "Team2", "Team3"};
    for (int i = 0; i < 3; i++) {
        data_t *user_data = malloc(sizeof(data_t));
        uuids[i] = malloc(sizeof(char) * UUID_LENGTH + 1);
        generate_uuid(uuids[i]);
        user_data = init_data(names[i], description[i], "NULL", uuids[i]);
        add_user_to_struct(user_data);
        teams_uuids[i] = malloc(sizeof(char) * UUID_LENGTH + 1);
        generate_uuid(teams_uuids[i]);
        add_team_to_struct(init_data(teams_names[i], "Description1", "NULL", teams_uuids[i]));
        add_user_to_team(uuids[i], teams_uuids[i]);
    }
    write_global_struct();
    if (global)
        free(global);
    sleep(0.5);
    global = malloc(sizeof(global_t));
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    load_global_struct();
    user_t *user1 = get_user_from_struct(uuids[0]);
    cr_assert_str_eq(user1->user_data->name, names[0]);
    cr_assert_str_eq(user1->user_data->description, description[0]);
    cr_assert_str_eq(user1->user_data->uuid, uuids[0]);
    cr_assert_eq(user1->is_logged, false);
    user_t *user2 = get_user_from_struct(uuids[1]);
    cr_assert_str_eq(user2->user_data->name, names[1]);
    cr_assert_str_eq(user2->user_data->description, description[1]);
    cr_assert_str_eq(user2->user_data->uuid, uuids[1]);
    cr_assert_eq(user2->is_logged, false);
    user_t *user3 = get_user_from_struct(uuids[2]);
    cr_assert_str_eq(user3->user_data->name, names[2]);
    cr_assert_str_eq(user3->user_data->description, description[2]);
    cr_assert_str_eq(user3->user_data->uuid, uuids[2]);
    cr_assert_eq(user3->is_logged, false);
    team_t *team1 = get_team_from_struct(teams_uuids[0]);
    cr_assert_not_null(team1);
    cr_assert_str_eq(team1->team_data->name, teams_names[0]);
    cr_assert_str_eq(team1->team_data->description, "Description1");
    cr_assert_str_eq(team1->team_data->uuid, teams_uuids[0]);
    team_t *team2 = get_team_from_struct(teams_uuids[1]);
    cr_assert_not_null(team2);
    cr_assert_str_eq(team2->team_data->name, teams_names[1]);
    cr_assert_str_eq(team2->team_data->description, "Description1");
    cr_assert_str_eq(team2->team_data->uuid, teams_uuids[1]);
    team_t *team3 = get_team_from_struct(teams_uuids[2]);
    cr_assert_not_null(team3);
    cr_assert_str_eq(team3->team_data->name, teams_names[2]);
    cr_assert_str_eq(team3->team_data->description, "Description1");
    cr_assert_str_eq(team3->team_data->uuid, teams_uuids[2]);
    for (int i = 0; i < 3; i++) {
        free(uuids[i]);
        free(teams_uuids[i]);
    }
}
