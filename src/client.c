/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** client
*/

#include "../include/ftp.h"

void clients_connection(sock *socket_var)
{
    int port = 0;
    char *addr_ip;
    int new_socket;

    if (FD_ISSET(socket_var->server_fd, &socket_var->readfds)) {
        if ((new_socket = accept(socket_var->server_fd,
        (struct sockaddr *)&socket_var->address,
        (socklen_t *)&socket_var->addrlen)) < 0) {
            perror("accept");
            exit(84);
        }
        addr_ip = inet_ntoa(socket_var->address.sin_addr);
        port = ntohs(socket_var->address.sin_port);
        send_msg(new_socket, "Service ready for new user.", 220);
        socket_var->clients = add_client(socket_var,
        new_socket, addr_ip, port);
        printf("Client connected [%s:%d]\n", addr_ip, port);
    }
}

clients_s *event_client_disconnected(sock *socket_var, clients_s *clients)
{
    char buffer[MAXDATASIZE] = { 0 };
    char **table;

    if ((socket_var->valread = read(socket_var->sd, buffer,
    MAXDATASIZE)) == 0) {
        printf("Client disconnected [%s:%d]\n",
        clients->ip_addr, clients->port);
        close(socket_var->sd);
        return delete_client(socket_var, clients);
    } else {
        buffer[socket_var->valread - 1] = '\0';
        table = my_split(buffer, " \r\n");
        get_order(table, clients);
        table_free(table);
    }
    return clients;
}

void loop_check_disconnection(sock *socket_var)
{
    clients_s *clients = socket_var->clients;

    while (clients != NULL) {
        socket_var->sd = clients->control_fd;
        if (FD_ISSET(socket_var->sd, &socket_var->readfds))
            clients = event_client_disconnected(socket_var, clients);
        clients = clients && clients->next ? clients->next : NULL;
    }
}

void wait_client(sock *socket_var)
{
    if (listen(socket_var->server_fd, 3) < 0)
        error_server("listen", socket_var->server_fd);
}
