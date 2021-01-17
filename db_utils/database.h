#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

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

#define MAX_STR_LEN 100
#define MAX_ARR_LEN 100

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

int loadDict(char *filename, Dict *dict, int showDebug);

int initSpecificKey(Dict *dict, K key);

V get(Dict *dict, K key, int *wasFound);

int updateData(Dict *dict, K key, char **prefix, size_t prefixSize, char **suffix, size_t suffixSize, char **postfix,
               size_t postfixSize);

int printCollectedData(Dict *dict, K key);

#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
