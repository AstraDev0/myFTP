/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** server
*/

#include "../include/ftp.h"

int server(char *port, char *path)
{
    sock socket_var = init_varaible(port, path);

    init(&socket_var);
    wait_client(&socket_var);
    puts("Waiting for connections ...");
    while (1) {
        child_sockets_wait_activity(&socket_var);
        clients_connection(&socket_var);
        loop_check_disconnection(&socket_var);
    }
    clear(&socket_var, path);
    return 0;
}
