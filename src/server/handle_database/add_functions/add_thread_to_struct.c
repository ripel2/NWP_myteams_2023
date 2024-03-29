/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_thread_to_struct
*/

#include "data_struct_functions.h"

#include "data.h"
#include <string.h>
#include <unistd.h>
#include <time.h>

int add_thread_to_struct(const char *channel_uuid, data_t *user_data,
data_t *thread_data)
{
    thread_t *new_thread = malloc(sizeof(thread_t));
    channel_t *channel_selected = get_channel_from_struct(channel_uuid);

    if (new_thread == NULL)
        return (ERROR);
    if (channel_selected == NULL)
        return (ERROR);
    new_thread->thread_data = thread_data;
    new_thread->user_data = user_data;
    new_thread->creation_date = time(NULL);
    TAILQ_INIT(&new_thread->replies);
    TAILQ_INSERT_TAIL(&channel_selected->threads, new_thread, entries);
    return (SUCCESS);
}
