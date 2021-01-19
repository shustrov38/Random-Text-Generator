#include "DataParse.h"

char **createArray2D() {
    char **t = (char **) malloc(sizeof(char *) * MAX_ARR_LEN);
    for (int i = 0; i < MAX_ARR_LEN; ++i) {
        t[i] = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    }
    return t;
}


void initStruct1(raceInfo *RACE){
    for (int i = 0; i < MAX_STR_LEN; ++i) {
        RACE[i].action;
        RACE[i].name;
        RACE[i].notice;
        RACE[i].lap = 0;
        RACE[i].noteSize = 0;
    }
}


int noticeIndex(char s[MAX_STR_LEN]){
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

//int tabCount(char s[MAX_STR_LEN]) {
//    int i = 0, count = 0;
//    while (s[i] != '\n') {
//        while (s[i] == '\t' && s[i] != '\n') {
//            ++i;
//        }
//        while (s[i] != '\t' && s[i] != '\n') {
//            ++i;
//        }
//        count++;
//    }
//    return count;
//}


raceInfo *InfoParse(char *filename) {
    FILE *in = fopen(filename, "r");

    raceInfo *parseRace = (raceInfo *) malloc(sizeof(raceInfo) * MAX_ARR_LEN);

    int size = 0;
    initStruct1(parseRace);

    while (!feof(in)) {
        char curString[MAX_STR_LEN];
        int curLap;
        char curName[MAX_STR_LEN], curAct[MAX_STR_LEN], curNotice[MAX_STR_LEN];
        fgets(curString, MAX_STR_LEN, in);

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

    for (int i = 0; i < size; ++i) {
        printf("%d  %s  %s  ", parseRace[i].lap, parseRace[i].name, parseRace[i].action);
        for (int j = 0; j < parseRace[i].noteSize; ++j) {
            printf("%s  ", parseRace[i].notice[j]);
        }
        printf("\n");
    }

    //return parseRace;
}
