#ifndef MAIN_C_BEAUTIFIER_H
#define MAIN_C_BEAUTIFIER_H

#endif //MAIN_C_BEAUTIFIER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct word
{
    char *name;
    char **synonyms;
    size_t syn_size;
    char **adjectives;
    size_t adj_size;
}WORD;

//шаблон ввода
//#word
//##synonims
//...
//##adjectives
//...

typedef struct data
{
    WORD *words;
    size_t size;
    size_t capacity;
}DATA;

DATA create_data();

void update_data(DATA *data, char *word);

void update_word_syn(DATA *data, char *synonym);

void update_word_adj(DATA *data, char *adjective);

void parse(FILE *in, DATA *data);

void print_data(DATA *data);

