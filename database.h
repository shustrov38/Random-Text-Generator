#ifndef RANDOM_TEXT_GENERATOR_DATABASE_H
#define RANDOM_TEXT_GENERATOR_DATABASE_H


#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef char *K;
typedef char **V;

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


#endif //RANDOM_TEXT_GENERATOR_DATABASE_H
