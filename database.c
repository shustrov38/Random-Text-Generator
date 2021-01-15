#include "database.h"

// create Dict structure with valid data
Dict *createDict() {
    Dict *dict = (Dict *) malloc(sizeof(Dict));
    dict->capacity = 1;
    dict->size = 0;
    dict->data = (Entry **) malloc(sizeof(Entry *) * dict->capacity);
    return dict;
}

// Returns 1 if such a key already exists, otherwise returns 0
// {*index} is the position of founded key
__inline static int find(K key, Entry **data, size_t size, size_t *index) {
    int l = -1, r = size;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (CMP_LEQ(key, data[m]->key)) {
            r = m;
        } else {
            l = m;
        }
    }
    *index = r;
    return (r != size ? CMP_EQ(key, data[r]->key) : 0);
}
