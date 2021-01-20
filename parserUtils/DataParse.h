#ifndef RANDOM_TEXT_GENERATOR_DATAPARSE_H
#define RANDOM_TEXT_GENERATOR_DATAPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#ifndef RANDOM_TEXT_GENERATOR_UTILITIES_H
#include "../utilities.h"
#endif

typedef struct raceInfo {
    int lap;
    char name[MAX_STRING_LENGTH];
    char action[MAX_STRING_LENGTH];
    char notice[MAX_ARRAY_LENGTH][MAX_STRING_LENGTH];
    int noteSize;
} RaceInfo;

RaceInfo *parserCreate();

RaceInfo *parserLoadData(char *filename);

int parserGetSize();

#endif //RANDOM_TEXT_GENERATOR_DATAPARSE_H
