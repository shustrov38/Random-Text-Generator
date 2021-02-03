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
#include "namesUtils/nameChanger.h"

#define CHANCE_FOR_PHRASE 30
#define CHANCE_FOR_BEGINNING 70

char *getSentence(TemplateDictionary *dict, char *action) {
    int capacity = MAX_STRING_LENGTH;
    char *result = (char *) malloc(capacity * sizeof(char));
    if (!result) {
        fprintf(stderr, "Can't allocate memory {getSentence, result}");
        exit(-1);
    }
    memset(result, 0, capacity);

    char *prefix = tdGetRandomTemplate(dict, action, TD_PREFIX);
    if (prefix != NULL) {
        if (capacity - strlen(result) <= strlen(prefix)) {
            capacity *= 2;
            result = (char *) realloc(result, capacity * sizeof(char));
        }
        strcat(result, prefix);
        strcat(result, " ");
        prefix = NULL;
    }

    char *suffix = tdGetRandomTemplate(dict, action, TD_SUFFIX);
    if (suffix != NULL) {
        if (capacity - strlen(result) <= strlen(suffix)) {
            capacity *= 2;
            result = (char *) realloc(result, capacity * sizeof(char));
        }
        strcat(result, suffix);
        strcat(result, ". ");
        suffix = NULL;
    }

    if (rand() % 101 <= CHANCE_FOR_PHRASE) {

        char *postfix = tdGetRandomTemplate(dict, action, TD_POSTFIX);
        if (prefix != NULL) {
            if (capacity - strlen(result) <= strlen(postfix)) {
                capacity *= 2;
                result = (char *) realloc(result, capacity * sizeof(char));
            }
            strcat(result, postfix);
            strcat(result, " ");
            postfix = NULL;
        }

    }

    return result;
}

char *insertDataIntoSentence(char *sentence, RaceInfo *raceInfo) {
    int capacity = MAX_STRING_LENGTH;
    char *result = NULL;
    if (!(result = (char *) malloc(capacity * sizeof(char)))) {
        fprintf(stderr, "Can't allocate memory {insertDataIntoSentence, result}");
        exit(-1);
    }
    memset(result, 0, capacity);

    char **words = createArray2D();
    int wordsLength = 0;

    int i = 0, size = (int)strlen(sentence);

    while (i < size) {
        while (i < size && sentence[i] == ' ') ++i;
        char *word = createArray1D();

        int pos = i;
        while (i < size && sentence[i] != ' ') {
            word[i - pos] = sentence[i];
            ++i;
        }

        copyArray1D(words[wordsLength++], word);
        freeArray1D(word);
    }

    for (i = 0; i < wordsLength; ++i) {
        if (capacity - strlen(result) <= MAX_STRING_LENGTH) {
            capacity *= 2;
            result = (char *) realloc(result, capacity * sizeof(char));
        }

        if (strstr(words[i], "\\s1nc")) {
            strcat(result, getName(raceInfo->name, NAMES_NC));
        } else if (strstr(words[i], "\\s1gc")) {
            strcat(result, getName(raceInfo->name, NAMES_GC));
        } else if (strstr(words[i], "\\s1dc")) {
            strcat(result, getName(raceInfo->name, NAMES_DC));
        } else if (strstr(words[i], "\\s2nc")) {
            strcat(result, getName(raceInfo->notice[0], NAMES_NC));
        } else if (strstr(words[i], "\\s2gc")) {
            strcat(result, getName(raceInfo->notice[0], NAMES_GC));
        } else if (strstr(words[i], "\\s2dc")) {
            strcat(result, getName(raceInfo->notice[0], NAMES_DC));
        } else if (strstr(words[i], "\\n-\\dend")) {
            int number = atoi(raceInfo->notice[0]);
            strcat(result, raceInfo->notice[0]);
            strcat(result, (number == 3 ? "-им" : "-ым"));
        } else if (strstr(words[i], "\\n-\\cars")) {
            int number = atoi(raceInfo->notice[0]);
            char str[6];
            itoa(number, str, 10);
            strcat(result, str);
        } else if (strstr(words[i], "\\n")) {
            for (int k = 0; k < raceInfo->noteSize; ++k) {
                strcat(result, raceInfo->notice[k]);
                if (raceInfo->noteSize != 1 && k + 1 != raceInfo->noteSize) {
                    strcat(result, " ");
                }
            }
        } else if (strstr(words[i], "\\rand")) {
            int number = 1 + rand() % 10;
            char str[6];
            itoa(number, str, 10);
            strcat(result, str);
        } else {
            strcat(result, words[i]);
            goto spaceOnly;
        }

        int last = (int)strlen(words[i]) - 1;
        if (words[i][last] == '.') strcat(result, ".");
        else if (words[i][last] == ',') strcat(result, ",");
        else if (words[i][last] == '!') strcat(result, "!");
        else if (words[i][last] == '?') strcat(result, "?");
        else if (words[i][last] == '-') strcat(result, "-");
        else if (words[i][last] == ':') strcat(result, ":");
        else if (words[i][last] == '"') strcat(result, "\"");

        spaceOnly:
        strcat(result, " ");
    }

    freeArray2D(words);
    return result;
}

char *addBeginningToSentence(char *sentence, int flag) {
    int capacity = MAX_STRING_LENGTH;
    char *result = NULL;
    if (!(result = (char *) malloc(capacity * sizeof(char)))) {
        fprintf(stderr, "Can't allocate memory {addBeginningIntoSentence, result}");
        exit(-1);
    }
    memset(result, 0, capacity);

    if (flag) {
        strcat(result, "LOGIC_CON ");
    }

    if (capacity - strlen(result) <= strlen(sentence)) {
        capacity *= 2;
        result = (char *) realloc(result, capacity * sizeof(char));
    }
    strcat(result, sentence);

    return result;
}

char *beautifySentence(BeautifierData *data, char *sentence) {
    int resultLength = 0;
    int capacity = MAX_STRING_LENGTH;
    char *result = NULL;
    if (!(result = (char *) malloc(capacity * sizeof(char)))) {
        fprintf(stderr, "Can't allocate memory {beautifySentence, result}");
        exit(-1);
    }
    memset(result, 0, capacity);

    const char sep[] = " .,!-";

    int size = (int)strlen(sentence);
    char *word = createArray1D();

    for (int l, r = 0; r < size; ++r) {
        if (capacity == resultLength) {
            capacity *= 2;
            result = (char *) realloc(result, capacity * sizeof(char));
        }

        if (strspn(&sentence[r], sep)) {
            result[resultLength++] = sentence[r];
        } else {
            l = r;
            while (r < size && !strspn(&sentence[r], sep)) r++;
            memset(word, 0, MAX_STRING_LENGTH);
            for (int i = l; i < r; ++i) {
                word[i - l] = sentence[i];
            }

            char *synonym = btfGetRandDictValue(data, word, BTF_SYNONYM);

            int newSize = (int)strlen(synonym);
            for (int i = 0; i < newSize; ++i) {
                result[resultLength++] = synonym[i];
            }
            r--;
            synonym = NULL;
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

        if (cnt == 1) {
            break;
        }

        int step = spaces / (cnt - 1);

        // last stroke
        if (i == wordsLength && step >= 4) {
            for (int x = i - cnt; x < i; ++x) {
                fprintf(out, "%s ", words[x]);
            }
            break;
        }

        spaces -= step * (cnt - 1);

        // gen places for spaces
        int *place = (int *) malloc((cnt - 1) * sizeof(int));
        if (!place) {
            fprintf(stderr, "Can't allocate memory {marginedPrint, place}");
            exit(-1);
        }
        for (int k = 0; k < cnt - 1; ++k) {
            place[k] = 0;
        }

        for (int k = 0; k < spaces; ++k) {
            int pos = rand() % (cnt - 1);
            while (place[pos] == 1) {
                pos = (pos + 1) % (cnt - 1);
            }
            place[pos] = 1;
        }

        // print sentence
        for (int x = i - cnt, y = 0; x < i; ++x) {
            fprintf(out, "%s", words[x]);
            for (int sp = 0; sp < step; ++sp) {
                fprintf(out, " ");
            }
            if (spaces && place[y++] == 1) {
                --spaces;
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
        free(place);
    }

    fclose(out);
    freeArray2D(words);
}

void updateAction(char **positions, RaceInfo *raceInfo) {
    static int pSize = 0;

    if (!strcmp(raceInfo->action, "старт")) {
        // for start just insert name to right position
        int to = atoi(raceInfo->notice[0]);
        if (to <= 3) {
            strcat(raceInfo->action, "(хороший)");
        }
        if (to >= pSize) pSize = to + 1;
        strcpy(positions[to], raceInfo->name);
    } else if (!strcmp(raceInfo->action, "обгон")) {
        // swap two namesUtils
        int first = 0, second = 0;
        for (int j = 0; j < pSize; ++j) {
            if (!strcmp(positions[j], raceInfo->name)) {
                first = j;
            } else if (!strcmp(positions[j], raceInfo->notice[0])) {
                second = j;
            }
        }
        swapArray1D(positions[first], positions[second]);
        char t[][10] = {"(1)", "(2)"};
        strcat(raceInfo->action, t[rand() % 2]);
    } else if (!strcmp(raceInfo->action, "перемещ")) {
        // where 3 possible situations -> see ifs
        int to = atoi(raceInfo->notice[0]);
        if (to >= pSize) pSize = to + 1;

        int j = 0;
        for (; j < pSize; ++j) {
            if (!strcmp(positions[j], raceInfo->name)) {
                break;
            }
        }

        if (!strlen(positions[to])) {
            // move to empty position
            strcat(raceInfo->action, "(просто)");
            strcpy(positions[to], raceInfo->name);
            memset(positions[j], 0, MAX_STRING_LENGTH);
        } else {
            if (to < j) {
                // move upper in position list
                strcat(raceInfo->action, "(+)");

                int k = to;
                while (strlen(positions[k++]));
                if (k >= pSize) pSize = k + 1;

                for (; k != to; --k) {
                    strcpy(positions[k], positions[k - 1]);
                }

                strcpy(positions[to], raceInfo->name);
            } else {
                // move lower in position list
                strcat(raceInfo->action, "(-)");
                if (to >= pSize) pSize = to + 1;

                for (int k = j; k < to; ++k) {
                    strcpy(positions[k], positions[k + 1]);
                }

                strcpy(positions[to], raceInfo->name);
            }
        }
    } else if (!strcmp(raceInfo->action, "сход")) {
        // throw out
        int j = 0;
        for (; j < pSize; ++j) {
            if (!strcmp(positions[j], raceInfo->name)) {
                break;
            }
        }

        for (int k = j; k < pSize - 1; ++k) {
            strcpy(positions[k], positions[k + 1]);
        }

        --pSize;
    } else if (!strcmp(raceInfo->action, "финиш")) {
        // check winner
        int number = atoi(raceInfo->notice[0]);
        if (1 <= number && number <= 3) {
            strcat(raceInfo->action, "(1-3)");
        } else {
            strcat(raceInfo->action, "(ост)");
        }
    } else if (!strcmp(raceInfo->action, "лучшкруг")) {
        char t[][10] = {"(1)", "(2)"};
        strcat(raceInfo->action, t[rand() % 2]);
    }
}

char *getText(TemplateDictionary *tdDict, RaceInfo *raceInfo, BeautifierData *btfData, int showDebug) {
    int capacity = MAX_STRING_LENGTH;
    char *text = NULL;
    if (!(text = (char *) malloc(capacity * sizeof(char)))) {
        fprintf(stderr, "Can't allocate memory {getText, text}");
        exit(-1);
    }
    memset(text, 0, capacity);

    char **positions = createArray2D();

    for (int i = 0; i < parserGetSize(); ++i) {
        updateAction(positions, &raceInfo[i]);
        if (i + 1 == parserGetSize()) {
            strcpy(raceInfo[i].name, positions[1]);
        }

        char *template = getSentence(tdDict, raceInfo[i].action);
        char *sentenceWithData = insertDataIntoSentence(template, &raceInfo[i]);

        // conditions to add beginning
        int addBeg = (rand() % 101 <= CHANCE_FOR_BEGINNING) && (i != 0) && (i + 1 != parserGetSize());
        if (strstr(raceInfo[i].action, "старт")) addBeg = 0;
        if (strstr(raceInfo[i].action, "лидер")) addBeg = 0;
        if (strstr(raceInfo[i].action, "пейскар")) addBeg = 0;
        if (strstr(raceInfo[i].action, "лучшкруг")) addBeg = 0;
        if (strstr(raceInfo[i].action, "проблема")) addBeg = 0;
        char *sentenceWithBeginning = addBeginningToSentence(sentenceWithData, addBeg);

        char *beautifiedSentence = beautifySentence(btfData, sentenceWithBeginning);

        if (showDebug) {
            printf("\n%s\n%s\n", template, beautifiedSentence);
        }

        if (capacity - strlen(text) <= strlen(beautifiedSentence)) {
            capacity *= 2;
            text = (char *) realloc(text, capacity * sizeof(char));
        }

        strcat(text, beautifiedSentence);

        free(template);
        free(sentenceWithData);
        free(sentenceWithBeginning);
        free(beautifiedSentence);
    }

    freeArray2D(positions);
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
    parserLoadData("../protocol.txt", raceInfo);

    /* Beautifier Dictionary initialization */
    BeautifierData *btfData = btfCreateDict();
    btfParseDict("../btfUtils/synonyms.txt", btfData, 0);

    char *text = getText(tdDict, raceInfo, btfData, 0);
    tdDestroy(tdDict);
    btfDestroy(btfData);

    marginedPrint("../output.txt", text, 90);
    free(text);

    return EXIT_SUCCESS;
}