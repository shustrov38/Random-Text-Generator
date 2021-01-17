#include "DataParse.h"

char **createArray2D() {
    char **t = (char **) malloc(sizeof(char *) * MAX_ARR_LEN);
    for (int i = 0; i < MAX_ARR_LEN; ++i) {
        t[i] = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    }
    return t;
}

raceInfo *createStructArray() {
    raceInfo *t = (raceInfo *) malloc(sizeof(raceInfo) * MAX_ARR_LEN);
    return t;
}

void initStruct(raceInfo *RACE){
    for (int i = 0; i < MAX_STR_LEN; ++i) {
        RACE[i].action = (char *) malloc(sizeof(char) * MAX_STR_LEN);
        RACE[i].name = (char *) malloc(sizeof(char) * MAX_STR_LEN);
        RACE[i].notice = createArray2D();
        RACE[i].lap = 0;
        RACE[i].noteSize = 0;
    }
}

void InfoParse(char *filename){
    FILE *in = fopen(filename, "r");

    raceInfo *RACE = createStructArray();
    int SIZE = 0;
    initStruct(RACE);

    while (!feof(in)){
        char curString[MAX_STR_LEN];
        int curLap; char curName[MAX_STR_LEN], curAct[MAX_STR_LEN];
        fgets(curString, MAX_STR_LEN, in);
        sscanf(curString, "%d %s %s", &curLap, curName, curAct);
        //тут надо все action про»фать
        //пока есть только дл€ start
        if (strcmp(curAct, "старт") == 0) {
            char pos[MAX_STR_LEN];
            sscanf(curString, "%s", pos);
            //printf("%s\n", pos);
            RACE[SIZE].lap = curLap;
            strcpy(RACE[SIZE].name, curName);
            strcpy(RACE[SIZE].action, curAct);
            strcpy(RACE[SIZE].notice[0], pos);
            RACE[SIZE].noteSize++;

        }
        SIZE++;
    }

    for (int i = 0; i < SIZE; ++i){
        printf("%d  %s  %s  ", RACE[i].lap, RACE[i].name, RACE[i].action);
        if (RACE[i].noteSize > 0){
            for (int j = 0; j < RACE[i].noteSize; ++j){
                printf("%s  ", RACE[i].notice[j]);
            }
        } printf("\n");
    }


}
