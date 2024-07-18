/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** get_order
*/

#include "../include/ftp.h"

int send_msg(int sd, char *msg, int type)
{
    char *buffer;

    if (MAXDATASIZE < strlen(msg)) {
        fprintf(stderr, "message size too large");
        return 84;
    }
    if (!msg || type > 999)
        return 84;
    if ((buffer = malloc(3 + strlen(msg) + strlen("\r\n") + 2)) == 0)
        return 84;
    if (sprintf(buffer, "%d %s%s", type, msg, "\r\n") <= 0 ||
    write(sd, buffer, strlen(buffer)) < 0)
        perror("error writing to socket_var");
    free(buffer);
    return 0;
}

int get_order_next(char **table, clients_s *clients)
{
    if (!strncmp(table[0], "HELP", 4))
        return send_msg(clients->control_fd, "Help OK", 214);
    if (!strncmp(table[0], "CWD", 3))
        return cwd(table, clients);
    if (!strncmp(table[0], "LIST", 4))
        return ls_list(table, clients);
    if (!strncmp(table[0], "DELE", 4))
        return delete_file(table, clients);
    if (!strncmp(table[0], "PWD", 3))
        return show_pwd(clients);
    if (!strncmp(table[0], "PASV", 4))
        return pasv(clients);
    if (!strncmp(table[0], "RETR", 4))
        return retr(clients, table);
    if (!strncmp(table[0], "STOR", 4))
        return stor(clients, table);
    if (!strncmp(table[0], "PORT", 4))
        return port(clients, table);
    return send_msg(clients->control_fd,
    "Command not implemented", 500);
}

int get_order(char **table, clients_s *clients)
{
    if (!strncmp(table[0], "USER", 4))
        return user(table, clients);
    if (!strncmp(table[0], "QUIT", 4))
        return send_msg(clients->control_fd,
        "Service closing control connection.", 221);
    if (!strncmp(table[0], "PASS", 4))
        return pass(table, clients);
    if (!clients->connected && (strncmp(table[0], "SYST", 4) != 0
    && strncmp(table[0], "FEAT", 4) != 0 && strncmp(table[0], "EPSV", 4) != 0))
        return send_msg(clients->control_fd,
        "Not logged in.", 530);
    if (!strncmp(table[0], "NOOP", 4))
        return send_msg(clients->control_fd, "NOOP OK", 200);
    if (!strncmp(table[0], "CDUP", 4))
        return cdup(clients);
    return get_order_next(table, clients);
}
