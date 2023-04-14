/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_thread_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>
#include <time.h>

int add_thread_to_struct(const char *channel_uuid, data_t *user_data,
data_t *thread_data)
{
    thread_t *new_thread = malloc(sizeof(thread_t));
    channel_t *channel_selected = get_channel_from_struct(channel_uuid);
    time_t timestamp = time(NULL);

    if (new_thread == NULL)
        return (84);
    if (channel_selected == NULL)
        global->dll->functions[CLIENT_ERROR_UNKNOWN_CHANNEL](channel_uuid);
    new_thread->thread_data = thread_data;
    new_thread->user_data = user_data;
    TAILQ_INIT(&new_thread->replies);
    TAILQ_INSERT_TAIL(&channel_selected->threads, new_thread, entries);
    global->dll->functions[CLIENT_PRINT_THREAD_CREATED]
    (new_thread->thread_data->uuid, new_thread->user_data->uuid,
    timestamp, new_thread->thread_data->name, new_thread->thread_data->body);
    return (0);
}
