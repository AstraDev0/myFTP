/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** authentification
*/

#include "../include/ftp.h"

int user(char **table, clients_s *clients)
{
    if (!table[1]) {
        send_msg(clients->control_fd, "Login not good", 530);
        return 84;
    }
    if (clients->user != NULL)
        free(clients->user);
    clients->user = malloc(sizeof(char) * strlen(table[1]) + 1);
    strcpy(clients->user, table[1]);
    send_msg(clients->control_fd, "User name okay, need password.", 331);
    return 0;
}

int pass(char **table, clients_s *clients)
{
    if (!clients->user) {
        send_msg(clients->control_fd, "USER <username> is required.", 503);
        return 84;
    }
    if (strcmp(clients->user, "Anonymous") || table[1])
        return send_msg(clients->control_fd, "Invalid user", 530);
    clients->connected = 1;
    return send_msg(clients->control_fd, "User logged in, proceed.", 230);
}
