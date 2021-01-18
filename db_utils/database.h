#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

TemplateDictionary *createTemplateDictionary();

void updateTemplateDictionary(TemplateDictionary *dict, Entry *e);

void printTemplateDictionary(TemplateDictionary *dict);

void loadTemplateDictionary(char *filename, TemplateDictionary *dict, int showDebug);

char *getRandomValueFromTemplateDictionary(TemplateDictionary *dict, char *key, int type);

/* database template
 #action
 ##prefix
 word (xN раз)
 --
 ##suffix
 word (xN раз)
 --
 ##postfix
 word (xN раз)
 --
 */

#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
