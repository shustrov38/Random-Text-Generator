#include "DataParse.h"

int size = 0;

RaceInfo *parserCreate() {
    RaceInfo *t = (RaceInfo *) malloc(sizeof(RaceInfo));
    return t;
}

void initStruct(RaceInfo *info) {
    for (int i = 0; i < MAX_ARRAY_LENGTH; ++i) {
        info[i].action;
        info[i].name;
        info[i].notice;
        info[i].lap = 0;
        info[i].noteSize = 0;
    }
}

int noticeIndex(char s[MAX_STRING_LENGTH]) {
    int i = 0, count = 0;
    while (count != 3) {
        while ((s[i] == '\t' || s[i] == ' ') && s[i] != '\n') {
            ++i;
        }
        while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
            ++i;
        }
        count++;
    }
    if (s[i] == '\n') {
        return -1;
    } else {
        while (s[i] == '\t' || s[i] == ' ') {
            ++i;
        }
        return i;
    }

}

RaceInfo *parserLoadData(char *filename) {
    FILE *in = fopen(filename, "r");

    RaceInfo *parseRace = (RaceInfo *) malloc(sizeof(RaceInfo) * MAX_ARRAY_LENGTH);

    initStruct(parseRace);

    while (!feof(in)) {
        char curString[MAX_STRING_LENGTH];
        int curLap;
        char curName[MAX_STRING_LENGTH], curAct[MAX_STRING_LENGTH], curNotice[MAX_STRING_LENGTH];
        fgets(curString, MAX_STRING_LENGTH, in);

        //1st variant of Parser
        int indexNotice = noticeIndex(curString) - 1;

        sscanf(curString, "%d%s%s", &curLap, curName, curAct);

        parseRace[size].lap = curLap;
        strcpy(parseRace[size].name, curName);
        strcpy(parseRace[size].action, curAct);


        int i = 0;
        while (indexNotice != strlen(curString) + 1) {
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

int parserGetSize() {
    return size;
}