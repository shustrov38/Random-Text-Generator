#ifndef RANDOM_TEXT_GENERATOR_DATAPARSE_H
#define RANDOM_TEXT_GENERATOR_DATAPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "../utilities.h"

#define DPinitSize 50

typedef struct raceInfo {
    int lap;
    char name[MAX_STRING_LENGTH];
    char action[MAX_STRING_LENGTH];
    char notice[MAX_ARRAY_LENGTH][MAX_STRING_LENGTH];
    int noteSize;
} RaceInfo;

RaceInfo *parserCreate();

void parserLoadData(char *filename, RaceInfo *parseRace);

int parserGetSize();

#endif //RANDOM_TEXT_GENERATOR_DATAPARSE_H
