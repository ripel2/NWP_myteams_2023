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

Test(add_team_to_struct, basic_test, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    char uuid[37];

    uuid[0] = '\0';
    generate_uuid(uuid);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", uuid, "Description", global);
    TAILQ_FOREACH(team, &global->teams, entries) {
        cr_assert_str_eq(team->name, "Lucas");
        cr_assert_str_eq(team->description, "Description");
        cr_assert_str_eq(team->uuid, uuid);
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_team_to_struct, multiple_team, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    char *name[3] = {"Lucas", "Louis", "Andréas"};
    int idx = 0;
    char *uuid[3] = {"00000000-0000-0000-0000-000000000000",
        "00000000-0000-0000-0000-000000000001",
        "00000000-0000-0000-0000-000000000002"};

    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", uuid[0], "Description", global);
    add_team_to_struct("Louis", uuid[1], "Description", global);
    add_team_to_struct("Andréas", uuid[2], "Description", global);
    TAILQ_FOREACH(team, &global->teams, entries) {
        cr_assert_str_eq(name[idx], team->name);
        cr_assert_str_eq(team->description, "Description");
        cr_assert_str_eq(team->uuid, uuid[idx]);
        idx++;
    }
    fini_dll(global->dll);
    free(global);
}

Test(add_team_to_struct, multiple_team_with_same_name, .init=redirect_all_stderr)
{
    global_t *global = malloc(sizeof(global_t));
    global->dll = init_dll();
    team_t *team;
    char *name[2] = {"Lucas", "Lucas"};
    char last_uuid[37] = "00000000-0000-0000-0000-000000000000";
    int idx = 0;
    char uuid[2][37];

    uuid[0][0] = '\0';
    uuid[1][0] = '\0';
    generate_uuid(uuid[0]);
    generate_uuid(uuid[1]);
    TAILQ_INIT(&global->users);
    TAILQ_INIT(&global->teams);
    add_team_to_struct("Lucas", uuid[0], "Description", global);
    add_team_to_struct("Lucas", uuid[1], "Description", global);
    TAILQ_FOREACH(team, &global->teams, entries) {
        if (team) {
            cr_assert_str_eq(name[idx], team->name);
            cr_assert_str_eq(team->description, "Description");
            cr_assert_str_eq(team->uuid, uuid[idx]);
            cr_assert_str_neq(team->uuid, last_uuid);
            last_uuid[0] = '\0';
            strcat(last_uuid, team->uuid);
            idx++;
        }
    }
    fini_dll(global->dll);
    free(global);
}
