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
#include "names/nameChanger.h"

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
        char *t = createArray1D();
        t = tdGetRandomTemplate(dict, action, TD_POSTFIX);
        if (t != NULL) {
            strcat(result, t);
            strcat(result, " ");
        }
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
                    ++i;
                    if (sentence[i] == 'n' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->name, NAMES_NC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
                    } else if (sentence[i] == 'g' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->name, NAMES_GC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
                    } else if (sentence[i] == 'd' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->name, NAMES_DC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
                    }
                } else {
                    ++i;
                    if (sentence[i] == 'n' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->notice[0], NAMES_NC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
                    } else if (sentence[i] == 'g' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->notice[0], NAMES_GC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
                    } else if (sentence[i] == 'd' && sentence[i + 1] == 'c') {
                        ++i;
                        char *name = getName(raceInfo->notice[0], NAMES_DC);
                        size_t nameSize = strlen(name);
                        for (int j = 0; j < nameSize; ++j) {
                            result[resultSize++] = name[j];
                        }
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

            char *synonym = btfGetRandDictValue(data, word, BTF_SYNONYM);

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
    if (margin > 150) margin = 150;
    if (margin < 60) margin = 60;

    char **words = createArray2D();
    int wordsLength = 0;

    int i = 0, size = (int) strlen(text);

    int nextIsUpper = 1;
    while (i < size) {
        while (i < size && text[i] == ' ') ++i;
        char *word = createArray1D();

        int pos = i;
        while (i < size && text[i] != ' ') {
            word[i - pos] = text[i];
            ++i;
        }

        if (nextIsUpper) {
            setUpper(word);
            nextIsUpper = 0;
        }

        if (strcspn(word, ".!") != strlen(word)) {
            nextIsUpper = 1;
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

char *getText(int maxLength, int rows, TemplateDictionary *tdDict, RaceInfo *raceInfo, BeautifierData *btfData, int showDebug) {
    char *text = (char *) malloc(maxLength * sizeof(char));
    memset(text, 0, maxLength);

    for (int i = 0; i < rows; ++i) {
        char *template = getSentence(tdDict, raceInfo[i].action);
        char *sentenceWithData = insertDataIntoSentence(template, &raceInfo[i]);
        if (showDebug) {
            printf("\n%s\n%s\n", template, sentenceWithData);
        }
        strcat(text, beautifySentence(btfData, sentenceWithData));
    }

    return text;
}

int main() {
    unsigned seed = time(0);
    rand();
    srand(seed);

    setlocale(LC_ALL, "Russian");
    createAlphabet();
    loadNames(0);

    /* Template Dictionary initialization */
    TemplateDictionary *tdDict = tdCreateNew();
    tdLoadData("../tdUtils/templates.txt", tdDict, 0);

    /* Input Data Parser initialization */
    RaceInfo *raceInfo = parserCreate();
    parserLoadData("../RaceInfo.txt", raceInfo);

    /* Beautifier Dictionary initialization */
    BeautifierData *btfData = btfCreateDict();
    btfParseDict("../btfUtils/synonyms.txt", btfData);

    char *text = getText(12000, 149, tdDict, raceInfo, btfData, 0);

    marginedPrint("../output.txt", text, 90);

    tdDestroy(tdDict);
    btfDestroy(btfData);

    return EXIT_SUCCESS;
}