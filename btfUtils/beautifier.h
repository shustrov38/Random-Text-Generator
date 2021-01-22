#ifndef MAIN_C_BEAUTIFIER_H
#define MAIN_C_BEAUTIFIER_H

#endif //MAIN_C_BEAUTIFIER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BTF_ADJECTIVE 0
#define BTF_SYNONYM 1

typedef struct word {
    char name[50];
    char **synonyms;
    size_t syn_size;
    char **adjectives;
    size_t adj_size;
} BTF_WORD;

//шаблон ввода
//#word
//##synonims
//...
//##adjectives
//...

typedef struct data {
    BTF_WORD **words;
    size_t size;
    size_t capacity;
} BTF_DATA;

BTF_DATA *btfCreateDict();

void btfParseDict(FILE *in, BTF_DATA *data);

void btfPrintDict(BTF_DATA *data);

char *btfGetRandDictValue(BTF_DATA *dict, char *key, int type);