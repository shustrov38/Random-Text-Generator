//
// Created by Alex on 17.01.2021.
//

#include "beautifier.h"


DATA create_data()
{
    DATA *data = (DATA*)malloc(sizeof(DATA));
    data->size=0;
    data->capacity=1;
    return *data;
}

void update_data(DATA *data, char *word)
{
    if(data->size==data->capacity)
    {
        data->capacity*=2;
        data = (DATA*)realloc(data, data->capacity*sizeof(DATA));
    }
    strcpy(data->words[data->size]->name, word);
    data->size++;
    data->words[data->size]->synonyms = (char **)malloc(100*sizeof(char*));
    data->words[data->size]->adjectives = (char **)malloc(100*sizeof(char*));
    for (int i = 0; i < 100; ++i) {
        data->words[data->size]->adjectives[i] = (char *) malloc(sizeof(char) * 100);
        data->words[data->size]->synonyms[i] = (char *) malloc(sizeof(char) * 100);
    }
    data->words[data->size]->syn_size=0;
    data->words[data->size]->adj_size=0;
}

void update_word_syn(DATA *data, char *synonym)
{
    strcpy(data->words[data->size]->synonyms[data->words[data->size]->syn_size], synonym);
    data->words[data->size]->syn_size++;
}

void update_word_adj(DATA *data, char *adjective)
{
    strcpy(data->words[data->size]->adjectives[data->words[data->size]->adj_size], adjective);
    data->words[data->size]->adj_size++;
}


