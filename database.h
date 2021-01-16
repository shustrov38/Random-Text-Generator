#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 100

typedef struct templates {
    char **prefix;
    char **suffix;
    char **postfix;
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

__inline static int find(K key, Entry **data, size_t size, size_t *index);

int raw_put(Dict *dict, Entry *e);

int put(Dict *dict, K key, V value);

V *get(Dict *dict, K key, int *wasFound);

int updatePrefix(Dict *dict, K key, char **value);

int updateSuffix(Dict *dict, K key, char **value);

int updatePostfix(Dict *dict, K key, char **value);

#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
