/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** nodes
*/

#include "../include/ftp.h"

void delete_clients(clients_s *clients)
{
    clients_s *tmp = clients;

    while (clients) {
        tmp = clients->next;
        free(clients);
        clients = tmp;
        clients = clients->next;
    }
}

void free_element(clients_s *client_delete)
{
    free(client_delete->user);
    free(client_delete->path);
    free(client_delete);
}

clients_s *delete_client(sock *socket_var, clients_s *client_delete)
{
    clients_s *save = client_delete;

    if (socket_var->clients == client_delete && !client_delete->next) {
        socket_var->clients = NULL;
        free_element(client_delete);
        return NULL;
    }
    if (socket_var->clients == client_delete && client_delete->next) {
        socket_var->clients = client_delete->next;
        free_element(client_delete);
        return socket_var->clients;
    }
    save = client_delete->prec;
    save->next = client_delete->next;
    free_element(client_delete);
    return save;
}

clients_s *add_client(sock *socket_var, int control_fd, char *ip_addr, int port)
{
    clients_s *clients = socket_var->clients;
    clients_s *save = clients;
    clients_s *client = malloc(sizeof(clients_s));

    client->control_fd = control_fd;
    client->port = port;
    client->ip_addr = ip_addr;
    client->path = create_path(socket_var->path_serv_default);
    client->next = NULL;
    client->user = NULL;
    client->connected = 0;
    client->pasv_socket.mode = FTP_MODE_NOTHING;
    if (clients == NULL)
        return client;
    while (clients->next != NULL)
        clients = clients->next;
    client->prec = clients;
    clients->next = client;
    return save;
}

void clear(sock *socket_var, char *path)
{
    delete_clients(socket_var->clients);
    free(path);
    FD_CLR(socket_var->server_fd, &socket_var->readfds);
    close(socket_var->server_fd);
    shutdown(socket_var->server_fd, SHUT_RDWR);
}
