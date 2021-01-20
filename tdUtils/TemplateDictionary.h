#ifndef RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H
#define RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#ifndef RANDOM_TEXT_GENERATOR_UTILITIES_H
#include "../utilities.h"
#endif

#define DICT_INIT_CAPACITY 4

#define TD_SEPARATE_SYMBOL "--"

#define TD_PREFIX 0
#define TD_SUFFIX 1
#define TD_POSTFIX 2

typedef struct {
    char *key;
    char **prefix, **suffix, **postfix;
    int prefixSize, suffixSize, postfixSize;
} Entry;

typedef struct {
    int capacity, size;
    Entry **data;
} TemplateDictionary;

TemplateDictionary *tdCreateNew();

void tdDestroy(TemplateDictionary *dict);

void tdPrintData(TemplateDictionary *dict);

void tdLoadData(char *filename, TemplateDictionary *dict, int showDebug);

char *tdGetRandomTemplate(TemplateDictionary *dict, char *key, int type);

#endif //RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H
