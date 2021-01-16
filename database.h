#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct templates {
    char **prefix;
    size_t prefixSize;
    char **suffix;
    size_t suffixSize;
    char **postfix;
    size_t postfixSize;
} Templates;

typedef char *K;
typedef Templates *V;

typedef struct entry_t {
    K key;
    V value;
} Entry;

#define CMP_EQ(a, b) (strcmp((a), (b)) == 0)
#define CMP_LEQ(a, b) (strcmp((a), (b)) <= 0)

typedef struct dict_t {
    size_t size, capacity;
    Entry **data;
} Dict;

Dict *createDict();

int initSpecificKey(Dict *dict, K key);

V get(Dict *dict, K key, int *wasFound);

int updateData(Dict *dict, K key, char **prefix, size_t prefixSize, char **suffix, size_t suffixSize, char **postfix,
               size_t postfixSize);

int printCollectedData(Dict *dict, K key);

#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
