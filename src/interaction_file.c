/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** interaction_file
*/

#include "../include/ftp.h"

int delete_file(char **table, clients_s *clients)
{
    if (!table[1])
        return send_msg(clients->control_fd,
        "Missing file name argument.", 501);
    chdir(clients->path);
    if (remove(table[1]) != 0)
        return send_msg(clients->control_fd, "File not removable.", 550);
    return send_msg(clients->control_fd, "Delete successful", 250);
}

int retr(clients_s *clients, char **table)
{
    FILE* fp;
    char buf[MAXDATASIZE];
    int byte_read;

    if (!table[1])
        return send_msg(clients->control_fd,
        "Missing file name argument.", 501);
    fp = fopen(table[1], "rb");
    if (!fp)
        return send_msg(clients->control_fd, "Failed to open file.", 550);
    if (mode_passive_or_active(clients) == 84 && fclose(fp) == 0)
        return 84;
    send_msg(clients->control_fd, "Opening data connection.", 150);
    while ((byte_read = fread(buf, 1, MAXDATASIZE, fp)) > 0)
        write(clients->pasv_socket.data_fd, buf, byte_read);
    fclose(fp);
    close(clients->pasv_socket.data_fd);
    send_msg(clients->control_fd, "Transfer complete.", 226);
}

int stor(clients_s *clients, char **table)
{
    FILE *file;
    char buf[MAXDATASIZE];
    int bytes_read = 0;

    if (!table[1])
        return send_msg(clients->control_fd,
        "Missing file name argument.", 501);
    if (!(file = fopen(table[1], "wb"))) {
        send_msg(clients->control_fd, "Cannot create file.\r\n", 550);
        return 84;
    }
    if (mode_passive_or_active(clients) == 84 && fclose(file) == 0)
        return 84;
    send_msg(clients->control_fd, "Ok to send data.", 150);
    while ((bytes_read = read(clients->pasv_socket.data_fd,
    buf, MAXDATASIZE)) > 0)
        fwrite(buf, 1, bytes_read, file);
    fclose(file);
    send_msg(clients->control_fd, "Transfer complete.", 226);
}
