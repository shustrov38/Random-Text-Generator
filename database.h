#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 100

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

__inline static void freeEntry(Entry **e);

#define FREE_ENTRY(e) freeEntry(e)

#define CMP_EQ(a, b) (strcmp((a), (b)) == 0)
#define CMP_LEQ(a, b) (strcmp((a), (b)) <= 0)

typedef struct dict_t {
    size_t size, capacity;
    Entry **data;
} Dict;

Dict *createDict();

__inline static int find(K key, Entry **data, size_t size, size_t *index);

int rawPut(Dict *dict, Entry *e);

int initSpecificKey(Dict *dict, K key);

V get(Dict *dict, K key, int *wasFound);

int printCollectedData(Dict *dict, K key);

#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
