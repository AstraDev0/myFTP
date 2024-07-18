/*
** EPITECH PROJECT, 2023
** B-PDG-300-BER-3-1-PDGD05-matthis.brocheton
** File description:
** my_split
*/

#include "../include/ftp.h"

int check_match(char c, char *separator, int count)
{
    if (separator[count] == c)
        return 1;
    if (separator[count] != '\0')
        return check_match(c, separator, count + 1);
    return 0;
}

int check_separator(char *str, char *separator, int v)
{
    if (check_match(str[v], separator, 0)
    && (v == 0 || str[v + 1] == '\0' || check_match(str[v + 1], separator, 0)))
        return 1;
    return 0;
}

int count_sprt(char *str, char *separator, int col, char **result)
{
    int count_letters = 0;
    int count_col = 0;
    int check_separator_match = 0;
    int count_st = 0;

    for (count_st; check_match(str[count_st], separator, 0); count_st++);
    for (int v = count_st; str[v] != '\0'; v++) {
        if (check_separator(str, separator, v))
            continue;
        if (count_col > col)
            break;
        check_separator_match = check_match(str[v], separator, 0);
        if (check_separator_match)
            count_col++;
        if (check_separator_match == 0 && col == count_col)
            count_letters++;
    }
    result[col] = malloc(sizeof(char) * (count_letters + 1));
    return count_letters;
}

char **separate_table(char **result, char *str, char *separator, int count_st)
{
    int count = 0;
    int count_result = 0;

    count_sprt(str, separator, count_result, result);
    for (int x = count_st; str[x]; x++) {
        if (check_separator(str, separator, x))
            continue;
        if (check_match(str[x], separator, 0)) {
            result[count_result++][count] = '\0';
            count = 0;
            count_sprt(str, separator, count_result, result);
        } else {
            result[count_result][count++] = str[x];
        }
    }
    result[count_result][count] = '\0';
    result[count_result + 1] = NULL;
    return result;
}

char **my_split(char *str, char *separator)
{
    int count = 1;
    char **result;
    int count_st = 0;

    for (count_st; check_match(str[count_st], separator, 0); count_st++);
    for (int v = count_st; str[v] != '\0'; v++) {
        if (check_separator(str, separator, v))
            continue;
        if (check_match(str[v], separator, 0))
            count++;
    }
    result = malloc(sizeof(char *) * (count + 1));
    return (separate_table(result, str, separator, count_st));
}
