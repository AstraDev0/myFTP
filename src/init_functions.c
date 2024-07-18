/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** init_functions
*/

#include "../include/ftp.h"

void init(sock *socket_var)
{
    if ((socket_var->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_server("socket_var failed", socket_var->server_fd);
    if (setsockopt(socket_var->server_fd, SOL_SOCKET, SO_REUSEADDR
    | 15, &socket_var->opt, sizeof(socket_var->opt)))
        error_server("setsockopt", socket_var->server_fd);
    socket_var->address.sin_family = AF_INET;
    socket_var->address.sin_addr.s_addr = INADDR_ANY;
    socket_var->address.sin_port = htons(atoi(socket_var->port_serv));
    if (bind(socket_var->server_fd, (struct sockaddr*)&socket_var->address,
    sizeof(socket_var->address)) < 0)
        error_server("bind failed", socket_var->server_fd);
}

sock init_varaible(char *port, char *path)
{
    sock socket_var;

    socket_var.port_serv = port;
    socket_var.path_serv_default = path;
    socket_var.opt = 1;
    socket_var.clients = NULL;
    socket_var.addrlen = sizeof(socket_var.address);
    return socket_var;
}

char *init_path_default(void)
{
    char cwd[1024];
    char *real_path;

    getcwd(cwd, sizeof(cwd));
    real_path = malloc(sizeof(char) * (strlen(cwd) + 1));
    strcpy(real_path, cwd);
    return real_path;
}
