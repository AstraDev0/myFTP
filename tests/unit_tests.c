/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** unit_tests
*/

#include "../include/ftp.h"
#include <criterion/redirect.h>
#include <criterion/criterion.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(usage, check_split, .init = redirect_all_std)
{
    usage();
}

Test(help, check_split, .init = redirect_all_std)
{
    char *argv[] = {"ftp_server", "-help", NULL};
    int argc = 2;
    start(argc, argv);
}

Test(herror, check_split, .init = redirect_all_std)
{
    char *argv[] = {"ftp_server", "-help", NULL};
    int argc = 1;
    start(argc, argv);
}

Test(herror2, check_split, .init = redirect_all_std)
{
    char *argv[] = {"ftp_server", "-help", NULL};
    int argc = 100;
    start(argc, argv);
}

Test(herror3, check_split, .init = redirect_all_std)
{
    char *argv[] = {NULL};
    int argc = 1;
    start(argc, argv);
}

Test(add_client, check_add_client)
{
    sock socket_var;
    clients_s *clients;
    socket_var.path_serv_default = "sss";
    clients = add_client(&socket_var, 1, "127.0.0.1", 8080);
}

Test(delete_client, check_delete_client)
{
    sock socket_var;
    clients_s *clients;
    socket_var.path_serv_default = "sss";
    clients = add_client(&socket_var, 1, "127.0.0.1", 8080);
    clients = delete_client(&socket_var, clients);
}

Test(separate_table, check_separate_table)
{
    char *str = "test1,test2,test3";
    char *separator = ",";
    int count = 3;
    char **result = malloc(sizeof(char*) * count);
    result = separate_table(result, str, separator, count);
}

Test(count_table, check_count_table)
{
    char **table = malloc(sizeof(char*) * 3);
    table[0] = "test1";
    table[1] = "test2";
    table[2] = "test3";
    int count = count_table(table, 3);
}

Test(init_varaible, check_init_varaible)
{
    char *port = "8080";
    char *path = "/tmp";
    sock socket_var = init_varaible(port, path);
}

Test(check_match, check_check_match)
{
    char c = ',';
    char *separator = ",";
    int count = 1;
    int result = check_match(c, separator, count);
}

Test(check_separator, check_check_separator)
{
    char *str = "test1,test2,test3";
    char *separator = ",";
    int v = check_separator(str, separator, 3);
}

Test(count_sprt, check_count_sprt)
{
    char *str = "test1,test2,test3";
    char *separator = ",";
    int col = 3;
    char **result = malloc(sizeof(char*) * col);
    int count = count_sprt(str, separator, col, result);
}
