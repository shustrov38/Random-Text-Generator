#include "database.h"


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

int raw_put(Dict *dict, Entry *e) {
    size_t l = -1, r = dict->size;
    size_t index;
    int contains;

    if (dict->size == 0) {
        dict->data[0] = e;
        dict->size++;
        return 0;
    }

    contains = find(e->key, dict->data, dict->size, &index);
    if (contains) {
        return 0;
    }

    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->data = (Entry **) realloc(dict->data, dict->capacity * sizeof(Entry *));
        if (dict == NULL) {
            exit(-5);
        }
    }

    memcpy(&(dict->data[index]), &(dict->data[index + 1]), (dict->size - index) * sizeof(Entry *));
    dict->data[index] = e;

    dict->size++;
    return 1;
}

int put(Dict *dict, K key, V value) {
    return 0;
}

V *get(Dict *dict, K key, int *wasFound) {
    return NULL;
}

int updatePrefix(Dict *dict, K key, char **value) {
    return 0;
}

int updateSuffix(Dict *dict, K key, char **value) {
    return 0;
}

int updatePostfix(Dict *dict, K key, char **value) {
    return 0;
}
