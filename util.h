//
// Created by nmertin on 05/05/16.
//

#ifndef Z_UTIL_H
#define Z_UTIL_H

#include <stddef.h>
#include <stdio.h>

int strfind(const char *str, char c);

int trim(char **str);

void toUpper(char **str);

size_t fread_all(unsigned char **buffer, const char *name);

template<class value>
void fwritev(const value &v, FILE *s) {
    fwrite(&v, sizeof(value), 1, s);
}

#endif //Z_UTIL_H
