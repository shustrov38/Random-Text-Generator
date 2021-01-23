#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#include "utilities.h"
#include "alphabetUtils/alphabet.h"
#include "parserUtils/DataParse.h"
#include "tdUtils/TemplateDictionary.h"
#include "btfUtils/beautifier.h"

#define SENTENCE_LENGTH 400
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

char *beautifySentence(BeautifierData *data, char *sentence) {
    size_t resultLength = 0;
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    memset(result, 0, SENTENCE_LENGTH);

    const char sep[] = " .,!-";

    size_t size = strlen(sentence);
    char *word = createArray1D();
    for (int l = 0, r = 0; r < size; ++r) {
        if (strspn(&sentence[r], sep)) {
            result[resultLength++] = sentence[r];
        } else {
            l = r;
            while (r < size && !strspn(&sentence[r], sep)) r++;
            memset(word, 0, 30 * sizeof(char));
            for (int i = l; i < r; ++i) {
                word[i - l] = sentence[i];
            }

            setLower(word);
            char *synonym = btfGetRandDictValue(data, word, BTF_SYNONYM);

            // got 1st word in sentence
            if (l == 0) setUpper(synonym);

            size_t newSize = strlen(synonym);
            for (int i = 0; i < newSize; ++i) {
                result[resultLength++] = synonym[i];
            }
            r--;
        }
    }
    freeArray1D(word);
    return result;
}

void marginedPrint(char *filename, char *text, int margin) {
    if (margin > 90) margin = 90;
    if (margin < 60) margin = 60;

    char **words = createArray2D();
    int wordsLength = 0;

    int i = 0, size = (int) strlen(text);
    while (i < size) {
        while (i < size && text[i] == ' ') ++i;
        char *word = createArray1D();
        int start = i;
        while (i < size && text[i] != ' ') {
            word[i - start] = text[i];
            ++i;
        }
        copyArray1D(words[wordsLength++], word);
        freeArray1D(word);
    }

    FILE *out = fopen(filename, "w");

    i = 0;
    while (i < wordsLength) {
        int length = 0, cnt = 0;
        while (i < wordsLength && length + cnt - 1 < margin) {
            ++cnt;
            length += (int) strlen(words[i++]);
        }
        if (length + cnt - 1 > margin) {
            --cnt;
            length -= (int) strlen(words[i - 1]);
            --i;
        }
        int spaces = margin - length;
        int step = spaces / (cnt - 1);

        // last stroke
        if (i == wordsLength && step >= 4) {
            for (int x = i - cnt; x < i; ++x) {
                fprintf(out, "%s ", words[x]);
            }
            break;
        }

        spaces -= step * (cnt - 1);
        for (int x = i - cnt; x < i; ++x) {
            fprintf(out, "%s", words[x]);
            for (int sp = 0; sp < step; ++sp) {
                fprintf(out, " ");
            }
            if (spaces) {
                --spaces;
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
    }
    fclose(out);

    freeArray2D(words);
}

int main() {
    unsigned seed = time(0);
    rand();
    srand(seed);

    setlocale(LC_ALL, "Russian");
    createAlphabet();

    /* Template Dictionary initialization */
    TemplateDictionary *dict = tdCreateNew();
    tdLoadData("../tdUtils/templates.txt", dict, 0);

    /* Input Data Parser initialization */
    RaceInfo *raceInfo = parserCreate();
    parserLoadData("../RaceInfo.txt", raceInfo);

    /* Beautifier Dictionary initialization */
    BeautifierData *btfData = btfCreateDict();
    btfParseDict("../btfUtils/input.txt", btfData);

    char *text = (char *) malloc(10000 * sizeof(char));
    memset(text, 0, 10000);

    for (int i = 0; i < 60; ++i) {
        char *sentence = getSentence(dict, raceInfo[i].action);
        char *sentenceWithData = insertDataIntoSentence(sentence, &raceInfo[i]);
        strcat(text, beautifySentence(btfData, sentenceWithData));
    }

//    printf("%s", text);
    marginedPrint("../output.txt", text, 120);

    tdDestroy(dict);

    return EXIT_SUCCESS;
}