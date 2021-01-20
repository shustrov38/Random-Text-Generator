#ifndef RANDOM_TEXT_GENERATOR_DATAPARSE_H
#define RANDOM_TEXT_GENERATOR_DATAPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define RACE_MAX_STR_LEN 200
#define RACE_MAX_ARR_LEN 200

typedef struct raceInfo {
    int lap;
    char name[RACE_MAX_STR_LEN];
    char action[RACE_MAX_STR_LEN];
    char notice[RACE_MAX_STR_LEN][RACE_MAX_STR_LEN]; int noteSize;
} raceInfo;

raceInfo *InfoParse(char *filename);

int returnSize();

#endif //RANDOM_TEXT_GENERATOR_DATAPARSE_H
