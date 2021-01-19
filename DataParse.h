#ifndef RANDOM_TEXT_GENERATOR_DATAPARSE_H
#define RANDOM_TEXT_GENERATOR_DATAPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 200
#define MAX_ARR_LEN 200

typedef struct raceInfo {
    int lap;
    char name[MAX_STR_LEN];
    char action[MAX_STR_LEN];
    char notice[MAX_STR_LEN][MAX_STR_LEN]; int noteSize;
} raceInfo;


raceInfo *createStructArray();

void initStruct(raceInfo *RACE);

char **createArray2D();

int countWrd(char string[MAX_STR_LEN]);

raceInfo *InfoParse(char *filename);

int tabCount(char s[MAX_STR_LEN]);

#endif //RANDOM_TEXT_GENERATOR_DATAPARSE_H
