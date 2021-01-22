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

char **createAlphabet(char **alphabet) {
    FILE *letterChangeFile = fopen("../UpperLower.txt", "r");
    for (int i = 0; i < 29; ++i) {
        fgets(alphabet[i], 29, letterChangeFile);
    }
    return alphabet;
}

int checkLetter(char word[30], char **alphabet) {
    int typeOfLetter = -1;
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][0]) {
            typeOfLetter = 0;
        }
        if (word[0] == alphabet[i][1]) {
            typeOfLetter = 1;
        }
    }

    return typeOfLetter;
}

char *getLower(char word[30], char **alphabet) {
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][0]) {
            word[0] = alphabet[i][1];
        }
    }
    return word;
}

char *getUpper(char word[30], char **alphabet) {
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][1]) {
            word[0] = alphabet[i][0];
        }
    }
    return word;
}

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
                    size_t nameSize = strlen(raceInfo->name);
                    for (int j = 0; j < nameSize; ++j) {
                        result[resultSize++] = raceInfo->name[j];
                    }
                } else {
                    size_t nameSize = strlen(raceInfo->notice[0]);
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

char *beautifySentence(BeautifierData *data, char *sentence, char **alphabet) {
    size_t resultSize = 0;
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    memset(result, 0, SENTENCE_LENGTH);

    const char sep[] = " .,!-";

    size_t size = strlen(sentence);
    char word[30];
    for (int l = 0, r = 0; r < size; ++r) {
        if (strspn(&sentence[r], sep)) {
            result[resultSize++] = sentence[r];
        } else {
            l = r;
            while (r < size && !strspn(&sentence[r], sep)) r++;
            memset(&word, 0, 30 * sizeof(char));
            for (int i = l; i < r; ++i) {
                word[i - l] = sentence[i];
            }


            int haveUpper = -1;
            haveUpper = checkLetter(word, alphabet);
            char *updatedWord = getLower(word, alphabet);
            char *newWord = btfGetRandDictValue(data, updatedWord, BTF_SYNONYM);
            if (!haveUpper) {
                newWord = getUpper(newWord, alphabet);
            }


            size_t newSize = strlen(newWord);
            for (int i = 0; i < newSize; ++i) {
                result[resultSize++] = newWord[i];
            }
            r--;
        }
    }

    return result;
}

int main() {
    unsigned seed = time(0);
    rand();
    srand(seed);

    setlocale(LC_ALL, "Russian");

    char **alphabet = createAlphabet(createArray2D());

    /* Template Dictionary initialization */
    TemplateDictionary *dict = tdCreateNew();
    tdLoadData("../tdUtils/templates.txt", dict, 0);

    /* Input Data Parser initialization */
    RaceInfo *raceInfo = parserCreate();
    parserLoadData("../RaceInfo.txt", raceInfo);

    /* Beautifier Dictionary initialization */
    BeautifierData *btfData = btfCreateDict();
    btfParseDict("../btfUtils/input.txt", btfData);

    for (int i = 0; i < 20; ++i) {
        char *sentence = getSentence(dict, raceInfo[i].action);
        char *newSentence = beautifySentence(btfData, sentence, alphabet);
        printf("%s", insertDataIntoSentence(newSentence, &raceInfo[i]));
    }

    tdDestroy(dict);

    return EXIT_SUCCESS;
}