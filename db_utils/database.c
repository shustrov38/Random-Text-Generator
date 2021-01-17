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

void pushTemplateDictionary(TemplateDictionary *dict, Entry *e) {
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        dict->data = (Entry **) realloc(dict->data, dict->capacity * sizeof(Entry *));
        if (!dict->data) {
            print_error(errno);
            exit(EXIT_FAILURE);
        }
    }
    dict->data[dict->size++] = e;
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
        printf("> Stored data for key {%s}:\n", e->key);

        printf("> prefix: [");
        for (int j = 0; j < e->prefixSize; ++j) {
            printf("%s", e->prefix[j]);
            if (j + 1 != e->prefixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("> suffix: [");
        for (int j = 0; j < e->suffixSize; ++j) {
            printf("%s", e->suffix[j]);
            if (j + 1 != e->suffixSize) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("> postfix: [");
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

    char *action = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char)),
            *check = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));

    int prefixSize, suffixSize, postfixSize;

    char **prefix = (char **) malloc(MAX_ARRAY_LENGTH * sizeof(char *));
    for (int i = 0; i < MAX_ARRAY_LENGTH; ++i) {
        prefix[i] = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));
    }

    char **suffix = (char **) malloc(MAX_ARRAY_LENGTH * sizeof(char *));
    for (int i = 0; i < MAX_ARRAY_LENGTH; ++i) {
        suffix[i] = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));
    }

    char **postfix = (char **) malloc(MAX_ARRAY_LENGTH * sizeof(char *));
    for (int i = 0; i < MAX_ARRAY_LENGTH; ++i) {
        postfix[i] = (char *) malloc(MAX_ARRAY_LENGTH * sizeof(char));
    }


    while (!feof(in)) {
        prefixSize = 0;
        suffixSize = 0;
        postfixSize = 0;

        fscanf(in, "%*c%s", action);

        for (int i = 0; i < 3; ++i) {
            fscanf(in, "%*s");
            while (1) {
                fscanf(in, "%s", check);

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

        Entry *e = (Entry *) malloc(sizeof(Entry));
        e->key = action;
        e->prefix = prefix;
        e->prefixSize = prefixSize;
        e->suffix = suffix;
        e->suffixSize = suffixSize;
        e->postfix = postfix;
        e->postfixSize = postfixSize;

        updateTemplateDictionary(dict, e);
    }

    if (showDebug) {
        printTemplateDictionary(dict);
    }

    fclose(in);
}