#include "TemplateDictionary.h"

Entry *createEntry() {
    Entry *e = (Entry *) malloc(sizeof(Entry));
    e->key = createArray1D();
    e->prefix = createArray2D();
    e->prefixSize = 0;
    e->suffix = createArray2D();
    e->suffixSize = 0;
    e->postfix = createArray2D();
    e->postfixSize = 0;
    return e;
}

void copyEntry(Entry *dst, Entry *src) {
    copyArray1D(dst->key, src->key);
    copyArray2D(dst->prefix, src->prefix);
    dst->prefixSize = src->prefixSize;
    copyArray2D(dst->suffix, src->suffix);
    dst->suffixSize = src->suffixSize;
    copyArray2D(dst->postfix, src->postfix);
    dst->postfixSize = src->postfixSize;
}

void freeEntry(Entry *e) {
    freeArray1D(e->key);
    freeArray2D(e->prefix);
    freeArray2D(e->suffix);
    freeArray2D(e->postfix);
    free(e);
}

TemplateDictionary *tdCreateNew() {
    TemplateDictionary *dict = (TemplateDictionary *) malloc(sizeof(TemplateDictionary));
    dict->capacity = DICT_INIT_CAPACITY;
    dict->size = 0;
    dict->data = (Entry **) malloc(dict->capacity * sizeof(Entry *));
    return dict;
}

void tdDestroy(TemplateDictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        freeEntry(dict->data[i]);
    }
    free(dict);
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

void tdUpdate(TemplateDictionary *dict, Entry *e) {
    int index, contains;
    contains = find(dict, e->key, &index);
    if (contains) {
        return;
    }
    pushTemplateDictionary(dict, e);
}

void tdPrintData(TemplateDictionary *dict) {
    printf("[DEBUG DB]\n");
    if (dict->size == 0) {
        printf("> TemplateDatabase is empty.\n");
        return;
    }
    for (int i = 0; i < dict->size; ++i) {
        Entry *e = createEntry();
        copyEntry(e, dict->data[i]);

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

        freeEntry(e);
    }
}

void tdLoadData(char *filename, TemplateDictionary *dict, int showDebug) {
    FILE *in = fopen(filename, "r");

    char *check = createArray1D();

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
                    if (!strcmp(check, TD_SEPARATE_SYMBOL)) {
                        break;
                    } else if (i == 0) {
                        copyArray1D(e->prefix[e->prefixSize++], check);
                    } else if (i == 1) {
                        copyArray1D(e->suffix[e->suffixSize++], check);
                    } else if (i == 2) {
                        copyArray1D(e->postfix[e->postfixSize++], check);
                    }
                }
            }
        }

        tdUpdate(dict, e);
        freeEntry(e);
    }

    if (showDebug) {
        tdPrintData(dict);
    }

    fclose(in);
}

char *tdGetRandomTemplate(TemplateDictionary *dict, char *key, int type) {
    int index, contains, i;
    contains = find(dict, key, &index);
    if (!contains) {
        return NULL;
    }

    if (type == TD_PREFIX) {
        i = rand() % dict->data[index]->prefixSize;
        return dict->data[index]->prefix[i];
    } else if (type == TD_SUFFIX) {
        i = rand() % dict->data[index]->suffixSize;
        return dict->data[index]->suffix[i];
    } else if (type == TD_POSTFIX) {
        i = rand() % dict->data[index]->postfixSize;
        return dict->data[index]->postfix[i];
    } else {
        fprintf(stderr, "Bad type format in {tdGetRandomTemplate}\n");
        exit(EXIT_FAILURE);
    }
}
