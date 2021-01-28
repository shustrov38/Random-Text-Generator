#ifndef RANDOM_TEXT_GENERATOR_NAMECHANGER_H
#define RANDOM_TEXT_GENERATOR_NAMECHANGER_H

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../utilities.h"

#define NAMES_GC 0
#define NAMES_DC 1
#define NAMES_NC 2

#define __CHANCE_FOR_CAT 30
#define __NAMECHANGER_NAME_SIZE 50
#define __NAMECHANGER_TAG_SIZE 4

typedef struct {
//    gc - roditelny
//    dc - datelny
//    nc - imenitelny
    char tag[__NAMECHANGER_TAG_SIZE],
            first_name_gc[__NAMECHANGER_NAME_SIZE],
            second_name_gc[__NAMECHANGER_NAME_SIZE],
            first_name_dc[__NAMECHANGER_NAME_SIZE],
            second_name_dc[__NAMECHANGER_NAME_SIZE],
            first_name_nc[__NAMECHANGER_NAME_SIZE],
            second_name_nc[__NAMECHANGER_NAME_SIZE];
} Name;

void loadNames(int showDebug);

char *getName(char *tag, int type);


#endif //RANDOM_TEXT_GENERATOR_NAMECHANGER_H
