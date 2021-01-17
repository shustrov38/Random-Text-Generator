//
// Created by Alex on 17.01.2021.
//

#include "beautifier.h"


DATA create_data()
{
    DATA *data;
    data->words = (WORD*)malloc(10*sizeof(WORD));
    data->size=0;
    data->capacity=1;
    return *data;
}

void update_data(DATA *data, char *word)
{
    if(data->size==data->capacity)
    {
        data->capacity*=2;
        data->words = (WORD*)realloc(data->words, data->capacity*sizeof(WORD));
    }
    strcpy(data->words[data->size].name, word);
    data->size++;
    data->words[data->size].synonyms = (char **)malloc(100*sizeof(char*));
    data->words[data->size].adjectives = (char **)malloc(100*sizeof(char*));
    for (int i = 0; i < 100; ++i) {
        data->words[data->size].adjectives[i] = (char *) malloc(sizeof(char) * 100);
        data->words[data->size].synonyms[i] = (char *) malloc(sizeof(char) * 100);
    }
    data->words[data->size].syn_size=0;
    data->words[data->size].adj_size=0;
}

void update_word_syn(DATA *data, char *synonym)
{
    strcpy(data->words[data->size].synonyms[data->words[data->size].syn_size], synonym);
    data->words[data->size].syn_size++;
}

void update_word_adj(DATA *data, char *adjective)
{
    strcpy(data->words[data->size].adjectives[data->words[data->size].adj_size], adjective);
    data->words[data->size].adj_size++;
}

void parse(FILE *in, DATA *data)
{
    char *string;
    fgets(string, 100, in);
    if(string[0]=='#' && string[1]!='#')
    {
        for(int i=1;i<strlen(string);i++)
        {
            string[i-1]=string[i];
        }
        update_data(data, string);
    }
    else if(string[0]=='#' && string[1]!='#' && string[2]=='s')
    {
        fgets(string, 100, in);
        update_word_syn(data, string);
        while(string[0]!='#')
        {
            fgets(string, 100, in);
            update_word_syn(data, string);
        }
    }
    else if(string[0]=='#' && string[1]!='#' && string[2]=='a')
    {
        fgets(string, 100, in);
        update_word_adj(data, string);
        while(string[0]!='#')
        {
            fgets(string, 100, in);
            update_word_adj(data, string);
        }
    }
}

void print_data(DATA *data)
{
    for(int i=0;i<data->size;i++)
    {
        printf("%s\n", data->words[i].name);
        printf("Synonyms: ");
        for(int j=0;j<data->words[i].syn_size;j++)
        {
            printf("%s ", data->words[i].synonyms[j]);
        }
        printf("\n");
        printf("Adjectives: ");
        for(int j=0;j<data->words[i].adj_size;j++)
        {
            printf("%s ", data->words[i].adjectives[j]);
        }
        printf("\n");
    }
};


