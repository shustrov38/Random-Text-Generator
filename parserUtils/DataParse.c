#include "DataParse.h"


static int parserSize = 0;

void initStruct(RaceInfo *info) {
    for (int i = 0; i < MAX_ARRAY_LENGTH; ++i) {
        memset(info[i].action, 0, MAX_STRING_LENGTH);
        memset(info[i].name, 0, MAX_STRING_LENGTH);
        memset(info[i].notice, 0, MAX_STRING_LENGTH);
        info[i].lap = 0;
        info[i].noteSize = 0;
    }
}

RaceInfo *parserCreate() {
    RaceInfo *t = (RaceInfo *) malloc(MAX_ARRAY_LENGTH * sizeof(RaceInfo));
    if (!t) {
        fprintf(stderr, "Can't allocate memory {parserCreate, t}");
        exit(-1);
    }
    initStruct(t);
    return t;
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

void parserLoadData(char *filename, RaceInfo *parseRace) {
    FILE *in = fopen(filename, "r");

    // optionally added parameter
    strcpy(parseRace[parserSize++].action, "начало");

    while (!feof(in)) {
        char curString[MAX_STRING_LENGTH];
        int curLap;
        char curName[MAX_STRING_LENGTH], curAct[MAX_STRING_LENGTH], curNotice[MAX_STRING_LENGTH];
        fgets(curString, MAX_STRING_LENGTH, in);

        //1st variant of Parser
        int indexNotice = noticeIndex(curString) - 1;

        sscanf(curString, "%d%s%s", &curLap, curName, curAct);

        parseRace[parserSize].lap = curLap;
        strcpy(parseRace[parserSize].name, curName);
        strcpy(parseRace[parserSize].action, curAct);


        int i = 0;
        while (indexNotice != strlen(curString) + 1) {
            if ((curString[indexNotice] == '\t' || curString[indexNotice] == '\n') && i != 0) {
                strcpy(parseRace[parserSize].notice[parseRace[parserSize].noteSize], curNotice);
                parseRace[parserSize].noteSize++;
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

        parserSize++;
    }

    // optionally added parameter
    strcpy(parseRace[parserSize++].action, "конец");
}

int parserGetSize() {
    return parserSize;
}