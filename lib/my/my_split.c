/*
** EPITECH PROJECT, 2021
** STR_WORD_TO_ARRAY
** File description:
** put an str into an array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "my.h"

bool is_separator(char c, char const *sep)
{
    if (c == '\0')
        return 0;
    while (*sep) {
        if (c == *sep)
            return true;
        sep++;
    }
    return false;
}

int my_tablen(char const *str, char const *sep)
{
    int tot = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] && is_separator(str[i], sep))
            tot++;
        while (str[i] && is_separator(str[i], sep))
            i++;
        if (str[i])
            i++;
    }
    return (tot + 1);
}

int my_len_word(char const *str, char const *sep)
{
    int tot = 0;

    while (str[tot] && is_separator(str[tot], sep) == 0)
        tot++;
    return tot;
}

char **my_split(char const *str, char const *sep)
{
    int i = 0;
    int j = 0;
    int k;
    char **tab = malloc(sizeof(char *) * (my_tablen(str, sep) + 1));

    while (str[i]) {
        while (str[i] && is_separator(str[i], sep) && str[i++]);
        if (str[i])
            tab[j] = malloc(sizeof(char) * (my_len_word(&str[i], sep) + 1));
        k = i;
        while (str[i] && !is_separator(str[i], sep)) {
            tab[j][i - k] = str[i];
            i++;
        }
        if (str[i - 1])
            tab[j][i - k] = '\0';
        j++;
    }
    tab[j] = NULL;
    return tab;
}
