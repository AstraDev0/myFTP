/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** start
*/

#include "../include/ftp.h"

int start(int ac, char **av)
{
    if (ac == 2 && !strcmp(av[1], "-help"))
        return usage();
    handle_error(ac, av);
    if (check_dir(av[2]) == 84)
        return 84;
    return server(av[1], init_path_default());
}
