/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** passive
*/

#include "../include/ftp.h"

int mode_passive_or_active(clients_s *clients)
{
    int addrlen = sizeof(clients->pasv_socket.address);
    int accpt_socket;

    if (clients->pasv_socket.mode == FTP_MODE_ACTIVE)
        return connect_to_port(clients);
    if (clients->pasv_socket.mode == FTP_MODE_NOTHING) {
        send_msg(clients->control_fd, "Use PORT or PASV first.", 425);
        return 84;
    }
    if ((accpt_socket = accept(clients->pasv_socket.data_fd,
        (struct sockaddr *)&clients->pasv_socket.address,
        (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(84);
    }
    close(clients->pasv_socket.data_fd);
    clients->pasv_socket.data_fd = accpt_socket;
    return 0;
}

int init_pasv(clients_s *clients, int *port_data, Pasv *pasv)
{
    if ((pasv->data_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_server("socket_var failed", pasv->data_fd);
    pasv->address.sin_family = AF_INET;
    pasv->address.sin_port = htons(*port_data);
    pasv->address.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, clients->ip_addr, &pasv->address.sin_addr);
    while (bind(pasv->data_fd,
    (const struct sockaddr *)&pasv->address,
    sizeof(pasv->address)) < 0) {
        *port_data = generate_random_number(1024, 65635);
        pasv->address.sin_port = htons(*port_data);
    }
    if (listen(pasv->data_fd, 100) < 0)
        error_server("listen", pasv->data_fd);
    return 0;
}

int pasv(clients_s *clients)
{
    int port_data = 1024;
    char *ip;
    char **split;
    char *result;

    init_pasv(clients, &port_data, &clients->pasv_socket);
    ip = inet_ntoa(clients->pasv_socket.address.sin_addr);
    split = my_split(ip, ".");
    result = malloc(sizeof(char) * (strlen(ip) + strlen(split[0])
    + strlen(split[1]) + strlen(split[2]) + strlen(split[3])
    + count_int(port_data / 256, 0) + count_int(port_data % 256, 0) + 30));
    sprintf(result, "Entering Passive Mode (%s,%s,%s,%s,%d,%d)",
    split[0], split[1], split[2], split[3], port_data / 256, port_data % 256);
    clients->pasv_socket.mode = FTP_MODE_PASSIVE;
    send_msg(clients->control_fd, result, 227);
    free(result);
    table_free(split);
    return 0;
}
