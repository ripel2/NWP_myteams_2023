/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_reply_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_reply_to_struct(const char *thread_uuid, data_t *user_data, data_t *reply_data)
{
    reply_t *new_reply = malloc(sizeof(reply_t));
    thread_t *thread_selected = get_thread_from_struct(thread_uuid);

    if (new_reply == NULL)
        return (ERROR);
    if (thread_selected == NULL)
        return (ERROR);
    new_reply->reply_data = reply_data;
    TAILQ_INSERT_TAIL(&thread_selected->replies, new_reply, entries);
    global->dll->functions[SERVER_EVENT_REPLY_CREATED]
    (thread_uuid, user_data->uuid, new_reply->reply_data->body);
    return (SUCCESS);
}
