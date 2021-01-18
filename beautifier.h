#ifndef MAIN_C_BEAUTIFIER_H
#define MAIN_C_BEAUTIFIER_H

#endif //MAIN_C_BEAUTIFIER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct word {
    char name[50];
    char **synonyms;
    size_t syn_size;
    char **adjectives;
    size_t adj_size;
} WORD;

//шаблон ввода
//#word
//##synonims
//...
//##adjectives
//...

typedef struct data {
    WORD **words;
    size_t size;
    size_t capacity;
} DATA;

DATA *createData();

void parse(FILE *in, DATA *data);

void printData(DATA *data);

