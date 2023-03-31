/*
** EPITECH PROJECT, 2023
** mynet/server
** File description:
** mynet server init functions
*/

#include "server.h"

/**
 * @brief Initialize a server_t structure with default values
 * @param server The server_t structure to initialize
 * @param port The port to listen on
*/
static void server_init_default_values(server_t *server, unsigned short port)
{
    memset(server, 0, sizeof(server_t));
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->fd = -1;
    server->blocking = true;
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    TAILQ_INIT(&server->clients);
}

int server_init(server_t *server, unsigned short port)
{
    int optval = 1;

    server_init_default_values(server, port);
    server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->fd == -1)
        return errno;
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR,
    &optval, sizeof(int)) == -1)
        return errno;
    if (bind(server->fd, (struct sockaddr *)&server->addr,
    (socklen_t)sizeof(server->addr)) == -1)
        return errno;
    if (listen(server->fd, SERVER_LISTEN_BACKLOG) == -1)
        return errno;
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_SET(server->fd, &server->read_fds);
    server->max_fd = server->fd;
    return 0;
}
