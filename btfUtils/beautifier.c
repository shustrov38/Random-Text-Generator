#include "beautifier.h"


BeautifierData *btfCreateDict() {
    BeautifierData *data = (BeautifierData *) malloc(sizeof(BeautifierData));
    if (!data) {
        fprintf(stderr, "Can't allocate memory {btfCreateDict, data}");
        exit(-1);
    }
    data->words = (BtfWord **) malloc(10 * sizeof(BtfWord *));
    if (!data->words) {
        fprintf(stderr, "Can't allocate memory {btfCreateDict, data->words}");
        exit(-1);
    }
    data->size = 0;
    data->capacity = 1;
    return data;
}

void btfMemUpdDict(BeautifierData *data, char *word) {
    if (data->size == data->capacity) {
        data->capacity *= 2;
        data->words = (BtfWord **) realloc(data->words, data->capacity * sizeof(BtfWord *));
    }
    data->words[data->size] = (BtfWord *) malloc(sizeof(BtfWord));
    data->words[data->size]->name = (char *) malloc(sizeof(char) * 50);
    strcpy(data->words[data->size]->name, word);
    data->words[data->size]->synonyms = (char **) malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        data->words[data->size]->synonyms[i] = (char *) malloc(sizeof(char) * 100);
    }
    data->words[data->size]->syn_size = 0;
    data->words[data->size]->last_ind = -1;
    data->size++;
}

void btfUpdDictSyn(BeautifierData *data, char *synonym) {
    strcpy(data->words[data->size - 1]->synonyms[data->words[data->size - 1]->syn_size], synonym);
    data->words[data->size - 1]->syn_size++;
}

void btfParseDict(char *filename, BeautifierData *data, int showDebug) {
    FILE *in = fopen("../btfUtils/synonyms.txt", "r");

    char *string = (char *) malloc(50 * sizeof(char));
    int flag = 0;
    while (!feof(in)) {
        fgets(string, 50, in);
        string[strlen(string) - 1] = '\0';
        if (string[0] == '#' && string[1] != '#') {
            btfMemUpdDict(data, string);
            for (int i = 1; i < strlen(string); i++) {
                string[i - 1] = string[i];
            }
            string[strlen(string) - 1] = '\0';
            flag = 0;
        }
        if (string[0] == '#' && string[1] == '#' && string[2] == 's') {
            flag = 1;
            continue;
        }

        if (flag == 1) btfUpdDictSyn(data, string);
    }

    for (int i = 0; i < data->size; ++i) {
        size_t size = strlen(data->words[i]->name);
        for (int j = 1; j < size; ++j) {
            data->words[i]->name[j - 1] = data->words[i]->name[j];
        }
        data->words[i]->name[size - 1] = '\0';
    }

    fclose(in);

    if (showDebug) {
        btfPrintDict(data);
    }
}

void btfPrintDict(BeautifierData *data) {
    for (int i = 0; i < data->size; i++) {
        printf("%s:\n", data->words[i]->name);
        for (int j = 0; j < data->words[i]->syn_size; j++) {
            printf("%s ", data->words[i]->synonyms[j]);
        }
        printf("\n");
    }
};

char *btfGetRandDictValue(BeautifierData *dict, char *key, int type) {
    int defIndX = -1;
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(key, dict->words[i]->name) == 0) {
            defIndX = i;
            break;
        }
    }
    if (type == BTF_SYNONYM) {
        if (defIndX == -1 || dict->words[defIndX]->syn_size == 0) {
            return key;
        }

        int j = rand() % dict->words[defIndX]->syn_size;

        if (dict->words[defIndX]->last_ind == j) {
            j = (j + 1) % (int)dict->words[defIndX]->syn_size;
        }

        dict->words[defIndX]->last_ind = j;
//        printf("%s", dict->words[defIndX]->synonyms[j]);
        return dict->words[defIndX]->synonyms[j];
    }
    return NULL;
}

void btfDestroy(BeautifierData *dict) {
    for (int i = 0; i < dict->size; ++i) {
        freeArray1D(dict->words[i]->name);
        freeBtfArray2D(dict->words[i]->synonyms, dict->words[i]->syn_size);
    }
    free(dict);
}

