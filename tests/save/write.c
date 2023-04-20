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

static void init_global(void)
{
    global = malloc(sizeof(global_t));
    TAILQ_INIT(&global->teams);
    TAILQ_INIT(&global->users);
}

Test(add_user_to_struct2, multiple_user_without_teams, .init=init_global)
{
    int nb_users = 0;
    char *names[] = {"Niska", "PNL", "Franky Vincent"};
    char *description[] = {"Rappeur", "Rappeur", "Zoukeur"};
    char **uuids = malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        data_t *user_data = malloc(sizeof(data_t));
        uuids[i] = malloc(sizeof(char) * UUID_LENGTH + 1);
        generate_uuid(uuids[i]);
        user_data = init_data(names[i], description[i], "NULL", uuids[i]);
        add_user_to_struct(user_data);
    }
    remove("my_teams.db");
    sleep(0.5);
    write_global_struct();
    FILE *fd = open_file("my_teams.db", "r");
    cr_assert_not_null(fd);
    fread(&nb_users, sizeof(int), 1, fd);
    sleep(0.1);
    cr_assert_eq(nb_users, 3);
    for (int i = 0; i < 3; i++) {
        data_t *data = malloc(sizeof(data_t));
        bool is_logged = false;
        int nb_team_uuids = 0;
        int nb_personal_discussion = 0;
        fread(data, sizeof(data_t), 1, fd);
        cr_assert_str_eq(data->name, names[i]);
        cr_assert_str_eq(data->description, description[i]);
        cr_assert_str_eq(data->body, "NULL");
        fread(&is_logged, sizeof(bool), 1, fd);
        cr_assert_eq(is_logged, false);
        fread(&nb_team_uuids, sizeof(int), 1, fd);
        cr_assert_eq(nb_team_uuids, 0);
        for (int j = 0; j < nb_team_uuids; j++) {
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            cr_assert_str_eq(uuid, "NULL");
        }
        fread(&nb_personal_discussion, sizeof(int), 1, fd);
        sleep(0.1);
        cr_assert_eq(nb_personal_discussion, 0);
        for (int j = 0; j < nb_personal_discussion; j++) {
            data_t *data2 = malloc(sizeof(data_t));
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(data2, sizeof(data_t), 1, fd);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            cr_assert_str_eq(data2->name, "NULL");
            cr_assert_str_eq(data2->description, "NULL");
            cr_assert_str_eq(data2->body, "NULL");
            cr_assert_str_eq(data2->uuid, "NULL");
            free(data2);
            free(uuid);
        }
    }
    fclose(fd);
}

Test(add_user_to_struct2, multiple_user_with_team, .init=init_global)
{
    int nb_users = 0;
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
    user_t *user = get_user_from_struct(uuids[0]);
    user_t *user2 = get_user_from_struct(uuids[1]);
    user_t *user3 = get_user_from_struct(uuids[2]);
    char *discussion_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
    char *message_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
    generate_uuid(discussion_uuid);
    add_personnal_discussion_to_struct(discussion_uuid, uuids[0], user2->user_data);
    generate_uuid(message_uuid);
    add_message_to_struct(user->user_data, init_data("NULL", "NULL", "NULL", discussion_uuid), init_data("Message1", "Test1", "Ouloulou", message_uuid));
    generate_uuid(discussion_uuid);
    add_personnal_discussion_to_struct(discussion_uuid, uuids[0], user3->user_data);
    generate_uuid(message_uuid);
    add_message_to_struct(user->user_data, init_data("NULL", "NULL", "zizi", discussion_uuid), init_data("Message2", "Test2", "Ouloulou", message_uuid));
    remove("my_teams.db");
    sleep(0.5);
    write_global_struct();
    FILE *fd = open_file("my_teams.db", "r");
    cr_assert_not_null(fd);
    fread(&nb_users, sizeof(int), 1, fd);
    sleep(0.2);
    cr_assert_eq(nb_users, 3);
    for (int i = 0; i < 3; i++) {
        data_t *data = malloc(sizeof(data_t));
        bool is_logged = false;
        int nb_team_uuids = 0;
        int nb_personal_discussion = 0;
        int nb_messages = 0;
        fread(data, sizeof(data_t), 1, fd);
        cr_assert_str_eq(data->name, names[i]);
        cr_assert_str_eq(data->description, description[i]);
        cr_assert_str_eq(data->body, "NULL");
        fread(&is_logged, sizeof(bool), 1, fd);
        cr_assert_eq(is_logged, false);
        fread(&nb_team_uuids, sizeof(int), 1, fd);
        cr_assert_eq(nb_team_uuids, 0);
        for (int j = 0; j < nb_team_uuids; j++) {
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            cr_assert_str_eq(uuid, "NULL");
        }
        fread(&nb_personal_discussion, sizeof(int), 1, fd);
        sleep(0.3);
        if (i == 0)
            cr_assert_eq(nb_personal_discussion, 2);
        else
            cr_assert_eq(nb_personal_discussion, 0);
        for (int j = 0; j < nb_personal_discussion; j++) {
            data_t *data2 = malloc(sizeof(data_t));
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(data2, sizeof(data_t), 1, fd);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            free(data2);
            free(uuid);
            fread(&nb_messages, sizeof(int), 1, fd);
            for (int k = 0; k < nb_messages; k++) {
                data_t *data3 = malloc(sizeof(data_t));
                data_t *data4 = malloc(sizeof(data_t));
                time_t time;
                fread(data3, sizeof(data_t), 1, fd);
                fread(data4, sizeof(data_t), 1, fd);
                fread(&time, sizeof(time_t), 1, fd);
                if (i == 0 && j == 0) {
                    cr_assert_str_eq(data4->name, "Message1");
                    cr_assert_str_eq(data4->description, "Test1");
                    cr_assert_str_eq(data4->body, "Ouloulou");
                } else if (i == 0 && j == 1) {
                    cr_assert_str_eq(data4->name, "Message2");
                    cr_assert_str_eq(data4->description, "Test2");
                    cr_assert_str_eq(data4->body, "Ouloulou");
                }
                free(data3);
                free(data4);
            }
        }
        free(data);
    }
    fclose(fd);
    sleep(1);
}

Test(add_user_to_struct2, multiple_user_with_simple_team, .init=init_global)
{
    int nb_users = 0;
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
    user_t *user = get_user_from_struct(uuids[0]);
    user_t *user2 = get_user_from_struct(uuids[1]);
    user_t *user3 = get_user_from_struct(uuids[2]);
    char *discussion_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
    char *message_uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
    generate_uuid(discussion_uuid);
    add_personnal_discussion_to_struct(discussion_uuid, uuids[0], user2->user_data);
    generate_uuid(message_uuid);
    add_message_to_struct(user->user_data, init_data("NULL", "NULL", "NULL", discussion_uuid), init_data("Message1", "Test1", "Ouloulou", message_uuid));
    generate_uuid(discussion_uuid);
    add_personnal_discussion_to_struct(discussion_uuid, uuids[0], user3->user_data);
    generate_uuid(message_uuid);
    add_message_to_struct(user->user_data, init_data("NULL", "NULL", "zizi", discussion_uuid), init_data("Message2", "Test2", "Ouloulou", message_uuid));
    remove("my_teams.db");
    sleep(0.5);
    write_global_struct();
    FILE *fd = open_file("my_teams.db", "r");
    cr_assert_not_null(fd);
    fread(&nb_users, sizeof(int), 1, fd);
    sleep(0.2);
    cr_assert_eq(nb_users, 3);
    for (int i = 0; i < 3; i++) {
        data_t *data = malloc(sizeof(data_t));
        bool is_logged = false;
        int nb_team_uuids = 0;
        int nb_personal_discussion = 0;
        int nb_messages = 0;
        fread(data, sizeof(data_t), 1, fd);
        cr_assert_str_eq(data->name, names[i]);
        cr_assert_str_eq(data->description, description[i]);
        cr_assert_str_eq(data->body, "NULL");
        fread(&is_logged, sizeof(bool), 1, fd);
        cr_assert_eq(is_logged, false);
        fread(&nb_team_uuids, sizeof(int), 1, fd);
        cr_assert_eq(nb_team_uuids, 0);
        for (int j = 0; j < nb_team_uuids; j++) {
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            cr_assert_str_eq(uuid, "NULL");
        }
        fread(&nb_personal_discussion, sizeof(int), 1, fd);
        if (i == 0)
            cr_assert_eq(nb_personal_discussion, 2);
        else
            cr_assert_eq(nb_personal_discussion, 0);
        for (int j = 0; j < nb_personal_discussion; j++) {
            data_t *data2 = malloc(sizeof(data_t));
            char *uuid = malloc(sizeof(char) * UUID_LENGTH + 1);
            fread(data2, sizeof(data_t), 1, fd);
            fread(uuid, sizeof(char), UUID_LENGTH + 1, fd);
            free(data2);
            free(uuid);
            fread(&nb_messages, sizeof(int), 1, fd);
            for (int k = 0; k < nb_messages; k++) {
                data_t *data3 = malloc(sizeof(data_t));
                data_t *data4 = malloc(sizeof(data_t));
                time_t time;
                fread(data3, sizeof(data_t), 1, fd);
                fread(data4, sizeof(data_t), 1, fd);
                fread(&time, sizeof(time_t), 1, fd);
                if (i == 0 && j == 0) {
                    cr_assert_str_eq(data4->name, "Message1");
                    cr_assert_str_eq(data4->description, "Test1");
                    cr_assert_str_eq(data4->body, "Ouloulou");
                } else if (i == 0 && j == 1) {
                    cr_assert_str_eq(data4->name, "Message2");
                    cr_assert_str_eq(data4->description, "Test2");
                    cr_assert_str_eq(data4->body, "Ouloulou");
                }
                free(data3);
                free(data4);
            }
        }
        free(data);
    }
    int nb_teams = 0;
    fread(&nb_teams, sizeof(int), 1, fd);
    cr_assert_eq(nb_teams, 3);
    for (int i = 0; i < 3; i++) {
        data_t *data = malloc(sizeof(data_t));
        fread(data, sizeof(data_t), 1, fd);
        sleep(0.1);
        cr_assert_str_eq(data->name, teams_names[i]);
        cr_assert_str_eq(data->description, "Description1");
        cr_assert_str_eq(data->body, "NULL");
        cr_assert_str_eq(data->uuid, teams_uuids[i]);
        int nb_channels = 0;
        fread(&nb_channels, sizeof(int), 1, fd);
        sleep(0.1);
        cr_assert_eq(nb_channels, 0);
    }
    fclose(fd);
}
