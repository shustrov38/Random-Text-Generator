#ifndef RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H
#define RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define DICT_INIT_CAPACITY 4

#define SEPARATE_SYMBOL "--"

#define PREFIX 0
#define SUFFIX 1
#define POSTFIX 2

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

void tdPrintData(TemplateDictionary *dict);

void tdLoadData(char *filename, TemplateDictionary *dict, int showDebug);

char *tdGetRandomTemplate(TemplateDictionary *dict, char *key, int type);

#endif //RANDOM_TEXT_GENERATOR_TEMPLATEDICTIONARY_H
