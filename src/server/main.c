/*
** EPITECH PROJECT, 2023
** mynet
** File description:
** mynet server main function
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"

global_t *global;

static dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    if (dll == NULL)
        return NULL;
    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

int main(int ac, char **av)
{
    global = malloc(sizeof(global_t));
    if (global == NULL)
        return ERROR;
    global->dll = init_dll();
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    data_t *user_data = init_data("user", "user", "user", "00000000-0000-0000-0000-000000000000");
    data_t *user_data_2 = init_data("user2", "user2", "user2", "00000000-0000-0000-0000-000000000001");
    data_t *message = init_data("message", "message", "message", "00000000-0000-0000-0000-000000000002");
    data_t *team_data = init_data("team", "team", "team", "00000000-0000-0000-0000-000000000003");
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team_data);
    add_user_to_struct(user_data);
    add_user_to_struct(user_data_2);
    add_personnal_discussion_to_struct("00000000-0000-0000-0000-000000000000", "00000000-0000-0000-0000-000000000000", user_data_2);
    get_personnal_discussion_from_struct("00000000-0000-0000-0000-000000000000");
    add_message_to_struct(user_data, user_data_2, message);
    add_user_to_team("00000000-0000-0000-0000-000000000003", "00000000-0000-0000-0000-000000000000");
    remove_user_from_team("00000000-0000-0000-0000-000000000003", "00000000-0000-0000-0000-000000000000");
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    return SUCCESS;
}
