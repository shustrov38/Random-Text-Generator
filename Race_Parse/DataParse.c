#include "DataParse.h"


int size = 0;

char **createArray2D() {
    char **t = (char **) malloc(sizeof(char *) * RACE_MAX_ARR_LEN);
    for (int i = 0; i < RACE_MAX_ARR_LEN; ++i) {
        t[i] = (char *) malloc(sizeof(char) * RACE_MAX_STR_LEN);
    }
    return t;
}

void initStruct1(raceInfo *RACE){
    for (int i = 0; i < RACE_MAX_STR_LEN; ++i) {
        RACE[i].action;
        RACE[i].name;
        RACE[i].notice;
        RACE[i].lap = 0;
        RACE[i].noteSize = 0;
    }
}

int noticeIndex(char s[RACE_MAX_STR_LEN]){
    int i = 0, count = 0;
    while (count != 3) {
        while((s[i] == '\t' || s[i] == ' ') && s[i] != '\n'){
            ++i;
        }
        while(s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
            ++i;
        }
        count++;
    }
    if(s[i] == '\n'){
        return -1;
    } else {
        while(s[i] == '\t' || s[i] == ' '){
            ++i;
        }
        return i;
    }

}

raceInfo *InfoParse(char *filename) {
    FILE *in = fopen(filename, "r");

    raceInfo *parseRace = (raceInfo *) malloc(sizeof(raceInfo) * RACE_MAX_ARR_LEN);

    initStruct1(parseRace);

    while (!feof(in)) {
        char curString[RACE_MAX_STR_LEN];
        int curLap;
        char curName[RACE_MAX_STR_LEN], curAct[RACE_MAX_STR_LEN], curNotice[RACE_MAX_STR_LEN];
        fgets(curString, RACE_MAX_STR_LEN, in);

        //1st variant of Parser
        int indexNotice = noticeIndex(curString) - 1;

        sscanf(curString, "%d%s%s", &curLap, curName, curAct);

        parseRace[size].lap = curLap;
        strcpy(parseRace[size].name, curName);
        strcpy(parseRace[size].action, curAct);


        int i = 0;
        while (indexNotice != strlen(curString)+1) {
            if ((curString[indexNotice] == '\t' || curString[indexNotice] == '\n') && i != 0) {
                strcpy(parseRace[size].notice[parseRace[size].noteSize], curNotice);
                parseRace[size].noteSize++;
                i = 0;
                memset(curNotice, 0, sizeof(curNotice));
            } else {
                if (i == 0) {
                    indexNotice++;
                }
                curNotice[i] = curString[indexNotice];
                ++i;
                ++indexNotice;
            }
        }

        size++;
    }

    size--;

    return parseRace;
}

int returnSize(){
    return size;
}