#ifndef MAIN_C_BEAUTIFIER_H
#define MAIN_C_BEAUTIFIER_H

#endif //MAIN_C_BEAUTIFIER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ADJECTIVE 0
#define SYNONYM 1

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

DATA *createBtfDict();

void parseBtfDict(FILE *in, DATA *data);

void printBtfDict(DATA *data);

char *getRandBtfDictValue(DATA *dict, char *key, int type);