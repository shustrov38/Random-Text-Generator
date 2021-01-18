#include "database.h"


#define MAX_ARRAY_LENGTH 50
#define MAX_STRING_LENGTH 50

char *createArray1D(int n) {
    char *t = (char *) malloc(n * sizeof(char));
    return t;
}

char **createArray2D(int n, int m) {
    char **t = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; ++i) {
        t[i] = createArray1D(m);
    }
    return t;
}

void copyArray1D(char *dst, char *src, int elementCount) {
    memcpy(dst, src, elementCount * sizeof(char));
}

void copyArray2D(char **dst, char **src, int elementCount) {
    for (int i = 0; i < elementCount; ++i) {
        copyArray1D(dst[i], src[i], elementCount);
    }
}

Entry *createEntry() {
    Entry *e = (Entry *) malloc(sizeof(Entry));
    e->key = createArray1D(MAX_STRING_LENGTH);
    e->prefix = createArray2D(MAX_ARRAY_LENGTH, MAX_STRING_LENGTH);
    e->prefixSize = 0;
    e->suffix = createArray2D(MAX_ARRAY_LENGTH, MAX_STRING_LENGTH);
    e->suffixSize = 0;
    e->postfix = createArray2D(MAX_ARRAY_LENGTH, MAX_STRING_LENGTH);
    e->postfixSize = 0;
    return e;
}

void copyEntry(Entry *dst, Entry *src) {
    memcpy(dst, src, sizeof(Entry));
}

TemplateDictionary *createTemplateDictionary() {
    TemplateDictionary *dict = (TemplateDictionary *) malloc(sizeof(TemplateDictionary));
    dict->capacity = DICT_INIT_CAPACITY;
    dict->size = 0;
    dict->data = (Entry **) malloc(dict->capacity * sizeof(Entry *));
    return dict;
}

inline static int find(TemplateDictionary *dict, char *key, int *index) {
    for (*index = 0; *index < dict->size; ++(*index)) {
        if (!strcmp(key, dict->data[*index]->key)) {
            return 1;
        }
    }
    return 0;
}

void pushTemplateDictionary(TemplateDictionary *dict, Entry *e) {
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        dict->data = (Entry **) realloc(dict->data, dict->capacity * sizeof(Entry *));
    }

    dict->data[dict->size] = createEntry();
    copyEntry(dict->data[dict->size], e);
    dict->size++;
}

void updateTemplateDictionary(TemplateDictionary *dict, Entry *e) {
    int index, contains;
    contains = find(dict, e->key, &index);
    if (contains) {
        return;
    }
    pushTemplateDictionary(dict, e);
}

void printTemplateDictionary(TemplateDictionary *dict) {
    printf("[DEBUG DB]\n");
    if (dict->size == 0) {
        printf("> TemplateDatabase is empty.\n");
        return;
    }
    for (int i = 0; i < dict->size; ++i) {
        Entry *e = dict->data[i];
        printf("> [%d] Stored data for key {%s}:\n", i + 1, e->key);

        printf("\t<prefix> : [");
        for (int j = 0; j < e->prefixSize; ++j) {
            printf("%s", e->prefix[j]);
            if (j + 1 != e->prefixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("\t<suffix> : [");
        for (int j = 0; j < e->suffixSize; ++j) {
            printf("%s", e->suffix[j]);
            if (j + 1 != e->suffixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("\t<postfix> : [");
        for (int j = 0; j < e->postfixSize; ++j) {
            printf("%s", e->postfix[j]);
            if (j + 1 != e->postfixSize) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

void loadTemplateDictionary(char *filename, TemplateDictionary *dict, int showDebug) {
    FILE *in = fopen(filename, "r");

    char *check = createArray1D(MAX_STRING_LENGTH);

    while (!feof(in)) {
        Entry *e = createEntry();
        fscanf(in, "%*c%s", e->key);

        for (int i = 0; i < 3; ++i) {
            fscanf(in, "%*s");
            while (1) {
                fgets(check, MAX_STRING_LENGTH, in);
                size_t length = strlen(check);
                if (check[length - 1] == '\n') {
                    check[length - 1] = '\0';
                    length--;
                }
                if (length) {
                    if (!strcmp(check, SEPARATE_SYMBOL)) {
                        break;
                    } else if (i == 0) {
                        copyArray1D(e->prefix[e->prefixSize++], check, length);
                    } else if (i == 1) {
                        copyArray1D(e->suffix[e->suffixSize++], check, length);
                    } else if (i == 2) {
                        copyArray1D(e->postfix[e->postfixSize++], check, length);
                    }
                }
            }
        }

        updateTemplateDictionary(dict, e);
    }

    if (showDebug) {
        printTemplateDictionary(dict);
    }

    fclose(in);
}

char *getRandomValueFromTemplateDictionary(TemplateDictionary *dict, char *key, int type) {
    int index, contains, i;
    contains = find(dict, key, &index);
    if (!contains) {
        return NULL;
    }

    if (type == PREFIX) {
        i = rand() % dict->data[index]->prefixSize;
        return dict->data[index]->prefix[i];
    } else if (type == SUFFIX) {
        i = rand() % dict->data[index]->suffixSize;
        return dict->data[index]->suffix[i];
    } else if (type == POSTFIX) {
        i = rand() % dict->data[index]->postfixSize;
        return dict->data[index]->postfix[i];
    } else {
        fprintf(stderr, "Bad type format in {getRandomValueFromTemplateDictionary}\n");
        exit(EXIT_FAILURE);
    }
}
