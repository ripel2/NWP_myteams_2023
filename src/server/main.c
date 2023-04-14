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
    data_t *user = init_data("Lucas", "", "", "00000000-0000-0000-0000-000000000000");
    data_t *team = init_data("Team", "Description", "", "00000000-0000-0000-0000-000000000001");
    data_t *thread = init_data("Thread", "Description", "Body", "00000000-0000-0000-0000-000000000002");
    data_t *reply = init_data("Reply", "", "Body", "00000000-0000-0000-0000-000000000003");
    data_t *channel = init_data("Channel", "Description", "", "00000000-0000-0000-0000-000000000004");
    add_user_to_struct(user);
    add_team_to_struct("00000000-0000-0000-0000-000000000000", team);
    add_channel_to_struct("00000000-0000-0000-0000-000000000001", channel);
    add_thread_to_struct("00000000-0000-0000-0000-000000000004", user, thread);
    add_reply_to_struct("00000000-0000-0000-0000-000000000002", user, reply);
    reply_t *reply1 = get_reply_from_struct("00000000-0000-0000-0000-000000000003");
    if (reply1)
        printf("%s" , reply1->user_data->name);
    if (reply1 == NULL)
        printf("NULL");
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    return SUCCESS;
}
