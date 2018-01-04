//
// Created by nmertin on 05/05/16.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int strfind(const char *str, char c) {
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i)
        if (str[i] == c)
            return i;
    return -1;
}

void toUpper(char **str) {
    for(int i = 0; i < strlen(*str); ++i)
        if ((*str)[i] >= 'a' && (*str)[i] <= 'z')
            (*str)[i] += 'A' - 'a';
}

size_t fread_all(unsigned char **buffer, const char *name) {
    FILE *f = fopen(name, "rb");
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    *buffer = (unsigned char *)malloc(len);
    fread(*buffer, len, 1, f);
    fclose(f);
    return len;
}

int trim(char **str) {
    int off = 0;
    for (; **str == ' ' || **str == '\t' || **str == '\n' || **str == '\r'; ++*str, ++off);
    size_t l = strlen(*str);
    for (size_t i = l - 1; i; --i)
        if ((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\n' || (*str)[i] == '\r')
            (*str)[i] = 0;
        else
            break;
    return off;
}
