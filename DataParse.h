#ifndef RANDOM_TEXT_GENERATOR_DATAPARSE_H
#define RANDOM_TEXT_GENERATOR_DATAPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 100
#define MAX_ARR_LEN 100

typedef struct raceInfo {
    int lap;
    char *name;
    char *action;
    char **notice; int noteSize;
} raceInfo;

raceInfo *createStructArray();

void initStruct(raceInfo *RACE);

char **createArray2D();

void InfoParse(char *filename);

#endif //RANDOM_TEXT_GENERATOR_DATAPARSE_H
