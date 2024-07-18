/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** handle_error
*/

#include "../include/ftp.h"

void handle_error(int ac, char **av)
{
    if (ac <= 2) {
        fprintf(stderr, "Argument missing");
        exit(84);
    }
    if (ac > 3) {
        fprintf(stderr, "To many argument");
        exit(84);
    }
    for (int x = 0; x < av[1][x]; x++) {
        if (av[1][x] < 48 || av[1][x] > 57) {
            fprintf(stderr, "Invalid port");
            exit(84);
        }
    }
}

void error_server(char *message, int server_fd)
{
    perror(message);
    close(server_fd);
    exit(84);
}
