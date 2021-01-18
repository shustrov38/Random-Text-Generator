//
// Created by Alex on 17.01.2021
// Edited by Igor on 18.01.2021
// Designed by Hideo Kojima on 31.02.2021
//

#include "beautifier.h"

DATA *createData() {
    DATA *data = (DATA *) malloc(sizeof(DATA));
    data->words = (WORD **) malloc(10 * sizeof(WORD *));
    data->size = 0;
    data->capacity = 1;
    return data;
}

void updateData(DATA *data, char *word) {
    if (data->size == data->capacity) {
        data->capacity *= 2;
        data->words = (WORD **) realloc(data->words, data->capacity * sizeof(WORD *));
    }
    data->words[data->size] = (WORD *) malloc(sizeof(WORD));
    strcpy(data->words[data->size]->name, word);
    data->words[data->size]->synonyms = (char **) malloc(100 * sizeof(char *));
    data->words[data->size]->adjectives = (char **) malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        data->words[data->size]->adjectives[i] = (char *) malloc(sizeof(char) * 100);
        data->words[data->size]->synonyms[i] = (char *) malloc(sizeof(char) * 100);
    }
    data->words[data->size]->syn_size = 0;
    data->words[data->size]->adj_size = 0;
    data->size++;
}

void updateWordSyn(DATA *data, char *synonym) {
    strcpy(data->words[data->size - 1]->synonyms[data->words[data->size - 1]->syn_size], synonym);
    data->words[data->size - 1]->syn_size++;
}

void updateWordAdj(DATA *data, char *adjective) {
    strcpy(data->words[data->size - 1]->adjectives[data->words[data->size - 1]->adj_size], adjective);
    data->words[data->size - 1]->adj_size++;
}

void parse(FILE *in, DATA *data) {
    char *string = (char *) malloc(50 * sizeof(char));
    int flag = 0;
    while (!feof(in)) {
        fgets(string, 50, in);
        if (string[0] == '#' && string[1] != '#') {
            updateData(data, string);
            flag = 0;
        }
        if (string[0] == '#' && string[1] == '#' && string[2] == 's') {
            flag = 1;
            continue;
        }
        if (string[0] == '#' && string[1] == '#' && string[2] == 'a') {
            flag = 2;
            continue;
        }

        if (flag == 1) updateWordSyn(data, string);
        if (flag == 2) updateWordAdj(data, string);

    }

}

void printData(DATA *data) {
    for (int i = 0; i < data->size; i++) {
        printf("%s", data->words[i]->name);
        printf("Synonyms: \n");
        for (int j = 0; j < data->words[i]->syn_size; j++) {
            printf("%s", data->words[i]->synonyms[j]);
        }
        printf("\n");
        printf("Adjectives: \n");
        for (int j = 0; j < data->words[i]->adj_size; j++) {
            printf("%s", data->words[i]->adjectives[j]);
        }
        printf("\n");
    }
};

char *dictRandGet(DATA *dict, char *key, char *param) {
    int defIndX = 0;
    for (int i = 0; i < dict->size; i++){
        if (strcmp(key,dict->words[i]->name) == 0){
            defIndX = i;
            break;
        }
    }
    int stime;
    long ltime;
    ltime = time (NULL);
    stime = (int) ltime/2;
    srand(stime);
    rand();
    if (strcmp(param,"syn")==0) {
        int j = rand() % dict->words[defIndX]->syn_size;
        printf("%s", dict->words[defIndX]->synonyms[j]);
        return dict->words[defIndX]->synonyms[j];
    }
    rand();
    if (strcmp(param,"adj")==0) {
        int j = rand() % dict->words[defIndX]->adj_size;
        printf("%s", dict->words[defIndX]->adjectives[j]);
        return dict->words[defIndX]->adjectives[j];
    }

};