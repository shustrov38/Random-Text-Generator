#ifndef MAIN_C_BEAUTIFIER_H
#define MAIN_C_BEAUTIFIER_H

#endif //MAIN_C_BEAUTIFIER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../utilities.h"

#define BTF_ADJECTIVE 0
#define BTF_SYNONYM 1

typedef struct word {
    char *name;
    char **synonyms;
    size_t syn_size;
    int last_ind;
} BtfWord;

typedef struct data {
    BtfWord **words;
    size_t size;
    size_t capacity;
} BeautifierData;

BeautifierData *btfCreateDict();

void btfParseDict(char *filename, BeautifierData *data, int showDebug);

void btfPrintDict(BeautifierData *data);

char *btfGetRandDictValue(BeautifierData *dict, char *key, int type);

void btfDestroy(BeautifierData *dict);