/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** order_passife_active
*/

#include "../include/ftp.h"

int port_send_info(clients_s *clients, char **ip_split)
{
    char buff[1024] = { 0 };

    sprintf(buff, "%s.%s.%s.%s", ip_split[0], ip_split[1],
    ip_split[2], ip_split[3]);
    clients->pasv_socket.address.sin_addr.s_addr = inet_addr(buff);
    clients->pasv_socket.address.sin_port = htons((atoi(ip_split[4]) * 256)
    + atoi(ip_split[5]));
    clients->pasv_socket.mode = FTP_MODE_ACTIVE;
    send_msg(clients->control_fd, "Command okay.", 200);
    table_free(ip_split);
    return 0;
}

int port(clients_s *clients, char **table)
{
    char **ip_split;

    if (!table[1])
        return send_msg(clients->control_fd,
        "PORT <value> is required.", 503);
    if ((clients->pasv_socket.data_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_server("socket_var failed", clients->pasv_socket.data_fd);
    clients->pasv_socket.address.sin_family = AF_INET;
    ip_split = my_split(table[1], ",");
    if (count_table(ip_split, 0) != 6)  {
        table_free(ip_split);
        return send_msg(clients->control_fd,
        "Missing args", 503);
    }
    return port_send_info(clients, ip_split);
}

int connect_to_port(clients_s *clients)
{
    if (connect(clients->pasv_socket.data_fd,
    (struct sockaddr *)&clients->pasv_socket.address,
    sizeof(clients->pasv_socket.address)) < 0) {
        error_server("connect failed", clients->pasv_socket.data_fd);
        close(clients->pasv_socket.data_fd);
        return 84;
    }
    return 0;
}
