/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_private_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_personnal_discussion_to_struct(char *discussion_uuid,
char *current_user_uuid, data_t *user_data)
{
    user_t *user = get_user_from_struct(current_user_uuid);
    personal_discussion_t *personal = malloc(sizeof(personal_discussion_t));

    if (!user || !personal)
        return (84);
    personal->user_data = user_data;
    strcat(personal->uuid, discussion_uuid);
    TAILQ_INIT(&personal->messages);
    TAILQ_INSERT_TAIL(&user->discussions, personal, entries);
    return (0);
}
