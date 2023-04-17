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


dlloader_t *init_dll(void);
void fini_dll(dlloader_t *dll);
void redirect_all_stderr(void);

Test(remove_user_from_team, basic_test, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    user_t *user;
    team_uuid_t *team_uuid;
    data_t *user_data;
    data_t *team_data;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    generate_uuid(uuid);
    team_data = init_data("Lucas", "", "", uuid);
    add_team_to_struct(user_data->uuid, team_data);
    add_user_to_struct(user_data);
    add_user_to_team(user_data->uuid, team_data->uuid);
    remove_user_from_team(user_data->uuid, team_data->uuid);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
            cr_assert_null(team_uuid);
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(remove_user_from_team, multiple_team, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    user_t *user;
    team_uuid_t *team_uuid;
    data_t *user_data;
    data_t *team_data;
    char uuid[37] = "00000000-0000-0000-0000-000000000000";
    char team_uuids[3][37] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001", "00000000-0000-0000-0000-000000000002"};
    int idx = 0;

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    add_user_to_struct(user_data);
    team_data = init_data("Lucas", "", "", team_uuids[0]);
    add_team_to_struct(user_data->uuid, team_data);
    add_user_to_team(user_data->uuid, team_data->uuid);
    team_data = init_data("Lucas", "", "", team_uuids[1]);
    add_team_to_struct(user_data->uuid, team_data);
    add_user_to_team(user_data->uuid, team_data->uuid);
    team_data = init_data("Lucas", "", "", team_uuids[2]);
    add_team_to_struct(user_data->uuid, team_data);
    add_user_to_team(user_data->uuid, team_data->uuid);
    remove_user_from_team(user_data->uuid, team_uuids[1]);
    remove_user_from_team(user_data->uuid, team_uuids[2]);
    remove_user_from_team(user_data->uuid, team_uuids[0]);

    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
            cr_assert_null(team_uuid);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}

Test(remove_user_from_team, bad_team_uuid, .init=redirect_all_stderr)
{
    global = malloc(sizeof(global_t));
    
    user_t *user;
    team_uuid_t *team_uuid;
    data_t *user_data;
    data_t *team_data;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    user_data = init_data("Lucas", "", "", uuid);
    generate_uuid(uuid);
    team_data = init_data("Lucas", "", "", uuid);
    add_team_to_struct(user_data->uuid, team_data);
    add_user_to_struct(user_data);
    add_user_to_team(user_data->uuid, team_data->uuid);
    cr_assert_eq(remove_user_from_team(user_data->uuid, team_data->uuid), 84);
    TAILQ_FOREACH(user, &global->users, entries) {
        TAILQ_FOREACH(team_uuid, &user->team_uuids, entries) {
            cr_assert_not_null(team_uuid);
        }
    }
    fini_dll(global->dll);
    free(global);
}
