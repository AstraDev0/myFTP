/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** select
*/

#include "../include/ftp.h"

void child_sockets_wait_activity(sock *socket_var)
{
    clients_s *save = socket_var->clients;

    FD_ZERO(&socket_var->readfds);
    FD_SET(socket_var->server_fd, &socket_var->readfds);
    int max_sd = socket_var->server_fd;
    while (save != NULL) {
        socket_var->sd = save->control_fd;
        if (socket_var->sd > 0)
            FD_SET(socket_var->sd, &socket_var->readfds);
        if (socket_var->sd > max_sd)
            max_sd = socket_var->sd;
        save = save->next;
    }
    socket_var->activity = select(max_sd + 1, &socket_var->readfds,
    NULL, NULL, NULL);
    if ((socket_var->activity < 0) && (errno != EINTR)) {
        printf("select error");
        exit(84);
    }
}
