/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** send_msg
*/

#include "../include/ftp.h"

void table_free(char **table)
{
    for (int i = 0; table[i]; i++)
        free(table[i]);
    free(table);
}

char *create_path(char *path)
{
    char *buffer = malloc(sizeof(char) * (strlen(path) + 1));

    strcpy(buffer, path);
    return buffer;
}

int count_int(int number, int i)
{
    if (number < 1)
        return i;
    return count_int(number / 10, i + 1);
}

int count_table(char **table, int i)
{
    if (!table[i])
        return i;
    count_table(table, i + 1);
}

int generate_random_number(int min, int max)
{
    srand(time(NULL));
    return (rand() % (max - min + 1)) + min;
}
