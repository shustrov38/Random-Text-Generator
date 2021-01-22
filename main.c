#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#include "utilities.h"
#include "parserUtils/DataParse.h"
#include "tdUtils/TemplateDictionary.h"
#include "btfUtils/beautifier.h"

#define SENTENCE_LENGTH 300
#define CHANCE_FOR_PHRASE 30

char *getSentence(TemplateDictionary *dict, char *action) {
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    memset(result, 0, SENTENCE_LENGTH);

    strcat(result, tdGetRandomTemplate(dict, action, TD_PREFIX));
    strcat(result, " ");
    strcat(result, tdGetRandomTemplate(dict, action, TD_SUFFIX));
    strcat(result, ". ");
    if (rand() % 101 <= CHANCE_FOR_PHRASE) {
        strcat(result, tdGetRandomTemplate(dict, action, TD_POSTFIX));
        strcat(result, " ");
    }

    return result;
}

char *insertDataIntoSentence(char *sentence, RaceInfo *raceInfo) {
    size_t resultSize = 0;
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    memset(result, 0, SENTENCE_LENGTH);

    size_t size = strlen(sentence);
    for (int i = 0; i < size; ++i) {
        if (sentence[i] != '\\') {
            result[resultSize++] = sentence[i];
        } else {
            ++i;
            if (sentence[i] == 's') {
                ++i;
                if (sentence[i] == '1') {
                    size_t nameSize=  strlen(raceInfo->name);
                    for (int j = 0; j < nameSize; ++j) {
                        result[resultSize++] = raceInfo->name[j];
                    }
                } else {
                    size_t nameSize=  strlen(raceInfo->notice[0]);
                    for (int j = 0; j < nameSize; ++j) {
                        result[resultSize++] = raceInfo->notice[0][j];
                    }
                }
            } else if (sentence[i] == 'n') {
                for (int k = 0; k < raceInfo->noteSize; ++k) {
                    size_t curNoticeSize = strlen(raceInfo->notice[k]);
                    for (int j = 0; j < curNoticeSize; ++j) {
                        result[resultSize++] = raceInfo->notice[k][j];
                    }
                    if (raceInfo->noteSize != 1 && k + 1 != raceInfo->noteSize) {
                        result[resultSize++] = ' ';
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    unsigned seed = time(0);
    rand();
    srand(seed);

    setlocale(LC_ALL, "Russian");

    /* Template Dictionary initialization */
    TemplateDictionary *dict = tdCreateNew();
    tdLoadData("../tdUtils/templates.txt", dict, 0);

    /* Input Data Parser initialization */
    RaceInfo *raceInfo = parserCreate();
    parserLoadData("../RaceInfo.txt", raceInfo);

    /* Beautifier Dictionary initialization */
    BeautifierData *data = btfCreateDict();
    btfParseDict("../btfUtils/input.txt", data);

    for (int i = 6; i < 12; ++i) {
        char *sentence = getSentence(dict, raceInfo[i].action);
        printf("%s", insertDataIntoSentence(sentence, &raceInfo[i]));
    }

    tdDestroy(dict);

    return EXIT_SUCCESS;
}