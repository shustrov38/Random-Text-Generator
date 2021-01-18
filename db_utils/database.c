#include "database.h"


#define MAX_ARRAY_LENGTH 100

void print_error(errno_t error_num) {
    const char *error_buf = strerror(error_num);
    fprintf(stderr, "[Error message] %s\n", error_buf);
}

TemplateDictionary *createTemplateDictionary() {
    TemplateDictionary *dict = (TemplateDictionary *) malloc(sizeof(TemplateDictionary));
    dict->capacity = DICT_INIT_CAPACITY;
    dict->size = 0;
    dict->data = (Entry **) malloc(dict->capacity * sizeof(Entry *));
    if (!dict->data) {
        print_error(errno);
        exit(EXIT_FAILURE);
    }
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

void pushTemplateDictionary(TemplateDictionary *dict, char *key, char **prefix, int prefixSize, char **suffix,
                            int suffixSize, char **postfix, int postfixSize) {
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        dict->data = (Entry **) realloc(dict->data, dict->capacity * sizeof(Entry *));
        if (!dict->data) {
            print_error(errno);
            exit(EXIT_FAILURE);
        }
    }
    dict->data[dict->size] = (Entry *) malloc(sizeof(Entry));

    dict->data[dict->size]->prefixSize = prefixSize;
    dict->data[dict->size]->suffixSize = suffixSize;
    dict->data[dict->size]->postfixSize = postfixSize;

    dict->data[dict->size]->key = createArray1D(MAX_ARRAY_LENGTH);
    dict->data[dict->size]->prefix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);
    dict->data[dict->size]->suffix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);
    dict->data[dict->size]->postfix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);

    memcpy(dict->data[dict->size]->key, key, strlen(key) * sizeof(char *));

    for (int i = 0; i < prefixSize; ++i) {
        memcpy(dict->data[dict->size]->prefix[i], prefix[i], prefixSize * sizeof(char *));
    }

    for (int i = 0; i < suffixSize; ++i) {
        memcpy(dict->data[dict->size]->suffix[i], suffix[i], suffixSize * sizeof(char *));
    }

    for (int i = 0; i < postfixSize; ++i) {
        memcpy(dict->data[dict->size]->postfix[i], postfix[i], postfixSize * sizeof(char *));
    }

    dict->size++;
}

void updateTemplateDictionary(TemplateDictionary *dict, char *key, char **prefix, int prefixSize, char **suffix,
                              int suffixSize, char **postfix, int postfixSize) {
    int index, contains;
    contains = find(dict, key, &index);
    if (contains) {
        return;
    }
    pushTemplateDictionary(dict, key, prefix, prefixSize, suffix, suffixSize, postfix, postfixSize);
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

        printf("\tprefix: [");
        for (int j = 0; j < e->prefixSize; ++j) {
            printf("%s", e->prefix[j]);
            if (j + 1 != e->prefixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("\tsuffix: [");
        for (int j = 0; j < e->suffixSize; ++j) {
            printf("%s", e->suffix[j]);
            if (j + 1 != e->suffixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("\tpostfix: [");
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

    char *action = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));
    char *check = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));

    int prefixSize, suffixSize, postfixSize;
    char **prefix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);
    char **suffix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);
    char **postfix = createArray2D(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH);


    while (!feof(in)) {
        prefixSize = 0;
        suffixSize = 0;
        postfixSize = 0;

        fscanf(in, "%*c%s", action);

        for (int i = 0; i < 3; ++i) {
            fscanf(in, "%*s");
            while (1) {
                fgets(check, MAX_ARRAY_LENGTH, in);
                size_t length = strlen(check);
                if (check[length - 1] == '\n') {
                    check[length - 1] = '\0';
                    length--;
                }
                if (length == 0) continue;

                if (!strcmp(check, "--")) break;

                if (i == 0) {
                    strcpy(prefix[prefixSize++], check);
                } else if (i == 1) {
                    strcpy(suffix[suffixSize++], check);
                } else {
                    strcpy(postfix[postfixSize++], check);
                }
            }
        }
        fscanf(in, "%*c");

        updateTemplateDictionary(dict, action, prefix, prefixSize, suffix, suffixSize, postfix, postfixSize);
    }

    if (showDebug) {
        printTemplateDictionary(dict);
    }

    fclose(in);
}