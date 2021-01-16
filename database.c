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
inline static int find(K key, Entry **data, size_t size, size_t *index) {
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

int rawPut(Dict *dict, Entry *e) {
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

int initSpecificKey(Dict *dict, K key) {
    Entry *e = (Entry *) malloc(sizeof(Entry));
    e->key = key;
    e->value = (Templates *) malloc(sizeof(Templates));

    e->value->prefix = NULL;
    e->value->prefixSize = 0;
    e->value->suffix = NULL;
    e->value->suffixSize = 0;
    e->value->postfix = NULL;
    e->value->postfixSize = 0;

    return rawPut(dict, e);
}

V get(Dict *dict, K key, int *wasFound) {
    size_t index;
    V returnValue = NULL;

    if (dict->size == 0) {
        *wasFound = 0;
    } else {
        *wasFound = find(key, dict->data, dict->size, &index);
        if (*wasFound) {
            returnValue = dict->data[index]->value;
        }
    }

    return returnValue;
}

int updateData(Dict *dict, K key, char **prefix, size_t prefixSize, char **suffix, size_t suffixSize, char **postfix,
               size_t postfixSize) {
    int wasFound;
    V collectedData = get(dict, key, &wasFound);
    if (!wasFound) {
        return 0;
    } else {
        collectedData->prefix = prefix;
        collectedData->prefixSize = prefixSize;
        collectedData->suffix = suffix;
        collectedData->suffixSize = suffixSize;
        collectedData->postfix = postfix;
        collectedData->postfixSize = postfixSize;
    }
    return 1;
}

int printCollectedData(Dict *dict, K key) {
    printf("[DEBUG DB]:\n");
    int wasFound;
    V collectedValue = get(dict, key, &wasFound);
    if (!wasFound) {
        printf("> There is no key {%s}\n", key);
        return 0;
    } else {
        printf("> Stored data for key {%s}:\n", key);
        if (collectedValue) {
            printf("> prefix: [");
            for (size_t i = 0; i < collectedValue->prefixSize; ++i) {
                printf("%s", collectedValue->prefix[i]);
                if (i + 1 != collectedValue->prefixSize) {
                    printf(", ");
                }
            }
            printf("]\n");

            printf("> suffix: [");
            for (size_t i = 0; i < collectedValue->suffixSize; ++i) {
                printf("%s", collectedValue->suffix[i]);
                if (i + 1 != collectedValue->suffixSize) {
                    printf(", ");
                }
            }
            printf("]\n");

            printf("> postfix: [");
            for (size_t i = 0; i < collectedValue->postfixSize; ++i) {
                printf("%s", collectedValue->postfix[i]);
                if (i + 1 != collectedValue->postfixSize) {
                    printf(", ");
                }
            }
            printf("]\n");
        } else {
            printf("Data for this key are not initialised.\n");
        }
    }
    return 1;
}
