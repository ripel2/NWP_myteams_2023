/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server step functions
*/

#include "server.h"

/**
 * @brief Remove clients that need to exit
 * @param server The server to remove clients from
*/
static void server_remove_clients(server_t *server)
{
    server_client_t *client = TAILQ_FIRST(&server->clients);
    server_client_t *tmp = NULL;

    while (client != NULL) {
        tmp = TAILQ_NEXT(client, entries);
        if (client->needs_exit == true) {
            close(client->fd);
            server_clear_client_lines(client);
            TAILQ_REMOVE(&server->clients, client, entries);
            free(client);
        }
        client = tmp;
    }
}

/**
 * @brief Set the max fd of the server and set the clients fds in the fd sets
 * @param server The server to set the max fd of
*/
static void server_setup_clients(server_t *server)
{
    server_client_t *client = NULL;

    server->max_fd = server->fd;
    TAILQ_FOREACH(client, &server->clients, entries) {
        FD_SET(client->fd, &server->read_fds);
        if (client->fd > server->max_fd)
            server->max_fd = client->fd;
    }
}

/**
 * @brief Select and accept a new client
 * @param server The server to accept a client on
 * @return 0 on success, the value of errno on failure
*/
static int server_select_and_accept(server_t *server)
{
    struct timeval timeout = {0, 0};
    struct timeval *timeout_ptr = server->blocking ? NULL : &timeout;
    int activity = 0;
    int new_socket = 0;
    socklen_t addrlen = sizeof(server->addr);

    activity = select(server->max_fd + 1, &server->read_fds,
    &server->write_fds, NULL, timeout_ptr);
    if (activity < 0 && errno != EINTR)
        return errno;
    if (!FD_ISSET(server->fd, &server->read_fds))
        return 0;
    new_socket = accept(server->fd, (struct sockaddr *)&server->addr,
    (socklen_t *)&addrlen);
    if (new_socket < 0)
        return errno;
    if (server_add_client(server, new_socket) == false)
        return ENOMEM;
    return 0;
}

/**
 * @brief Handle clients
 * @param server The server to handle clients on
*/
static void server_handle_clients(server_t *server)
{
    server_client_t *client = NULL;

    TAILQ_FOREACH(client, &server->clients, entries) {
        server_client_read_lines(server, client);
    }
}

int server_step(server_t *server)
{
    int ret = 0;

    server_remove_clients(server);
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_SET(server->fd, &server->read_fds);
    server_setup_clients(server);
    ret = server_select_and_accept(server);
    if (ret != 0)
        return ret;
    server_handle_clients(server);
    server_remove_clients(server);
    return 0;
}
