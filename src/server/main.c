/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"
#include "data_struct_functions.h"
#include "data.h"
#include "save.h"

global_t *global;

static dlloader_t *init_dll(void)
{
    dlloader_t *dll = malloc(sizeof(dlloader_t));

    if (dll == NULL)
        return NULL;
    load_teams_library("libs/myteams/libmyteams.so", dll);
    return dll;
}

void debug_init(void)
{
    char *name[] = {"Ninho", "NTM", "Booba", "Kaaris", "Niska", "Sofiane"};
    char *description[] = {"Salut a tous c'est Ninho", "So 80's", "Jambe de coq",
        "Membre du Zoulou Gang", "Matuidi charo", "Tout le monde s'en fou"};
    char *uuid[] = {"00000000-0000-0000-0000-000000000000",
        "11111111-1111-1111-1111-111111111111",
        "22222222-2222-2222-2222-222222222222",
        "33333333-3333-3333-3333-333333333333",
        "44444444-4444-4444-4444-444444444444",
        "55555555-5555-5555-5555-555555555555"};
    add_team_to_struct("00000000-0000-0000-0000-000000000000", init_data("Les Ziguigui", "Gang de la Paname", "BOUBOULLLEE", "00000000-0000-0000-0000-111111111111"));
    add_team_to_struct("00000000-0000-0000-0000-000000000000", init_data("Les Zoulous", "Gang de la banlieue", "BOUBOULLLEE", "00000000-0000-0000-0000-222222222222"));
    for (int i = 0; i < 6; i++) {
        data_t *data = init_data(name[i], description[i], "BOUBOULLLEE", uuid[i]);
        add_user_to_struct(data);
        if (strcmp(name[i], "Ninho") == 0 || strcmp(name[i], "Niska") == 0) {
            add_user_to_team("00000000-0000-0000-0000-111111111111", uuid[i]);
            add_user_to_team("00000000-0000-0000-0000-222222222222", uuid[i]);
        } else
            add_user_to_team("00000000-0000-0000-0000-222222222222", uuid[i]);
    }
    user_t *user = get_user_from_struct("11111111-1111-1111-1111-111111111111");
    user_t *user2 = get_user_from_struct("22222222-2222-2222-2222-222222222222");
    add_personnal_discussion_to_struct("00000000-0000-0000-1111-111111111111", "22222222-2222-2222-2222-222222222222", user->user_data);
    add_message_to_struct(user->user_data, user2->user_data, init_data("Discussion perso", "Discussion perso", "BOUBOULLLEE", "00000000-1111-0000-0000-000000000000"));
}

int main(int ac, char **av)
{
    global = malloc(sizeof(global_t));
    if (global == NULL)
        return ERROR;
    global->dll = init_dll();
    if (global->dll == NULL)
        return ERROR;
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
    print_help_if_needed(ac, av);
    is_port_valid(av[1]);
    debug_init();
    write_global();
    return SUCCESS;
}
