#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <stdlib.h>

typedef char *K;
typedef char **V;

typedef struct entry_t {
    K key;
    V value;
} Entry;

typedef struct dict_t {
    size_t size, capacity;
    Entry **data;
} Dict;

Dict *createDict();


#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
