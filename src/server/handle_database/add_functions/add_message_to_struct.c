/*
** EPITECH PROJECT, 2023
** NWP_myteams_2023 [WSL: Ubuntu]
** File description:
** add_message_to_struct
*/

#include "data_struct_functions.h"
#include "loader.h"
#include "data.h"
#include <string.h>
#include <unistd.h>

int add_message_to_struct(data_t *sender_uuid, data_t *receiver_uuid,
data_t *message)
{
    user_t *user = get_user_from_struct(sender_uuid->uuid);
    personal_discussion_t *discussion =
    get_personnal_discussion_from_struct(receiver_uuid->uuid);
    message_t *msg = malloc(sizeof(message_t));

    if (!user || !discussion || !msg)
        return (84);
    msg->user_data = sender_uuid;
    msg->message_data = message;
    global->dll->functions[SERVER_EVENT_PRIVATE_MESSAGE_SENDED]
    (sender_uuid->uuid, receiver_uuid->uuid, message->body);
    TAILQ_INSERT_TAIL(&discussion->messages, msg, entries);
    return (0);
}
