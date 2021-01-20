#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "Race_Parse/DataParse.h"
#include "tdUtils/TemplateDictionary.h"

#define SENTENCE_LENGTH 200
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
        strcat(result, ". ");
    }

    return result;
}

char *insertDataIntoSentence(char *sentence, char *name, char *position) {
    size_t size = strlen(sentence), nameSize = strlen(name), positionSize = strlen(position);

    size_t resultSize = 0;
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    memset(result, 0, SENTENCE_LENGTH);

    for (int i = 0; i < size; ++i) {
        if (sentence[i] != '\\') {
            result[resultSize++] = sentence[i];
        } else {
            ++i;
            if (sentence[i] == 's') {
                for (int j = 0; j < nameSize; ++j) {
                    result[resultSize++] = name[j];
                }
            } else if (sentence[i] == 'p') {
                for (int j = 0; j < positionSize; ++j) {
                    result[resultSize++] = position[j];
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

    TemplateDictionary *dict = tdCreateNew();
    tdLoadData("../tdUtils/templates.txt", dict, 0);

    char *action = "�����", *sentence;
    for (int i = 0; i < 10; ++i) {
        sentence = getSentence(dict, action);
        printf("%s\n", insertDataIntoSentence(sentence, "������", "12"));
    }
    printf("\n");

    tdDestroy(dict);

    return EXIT_SUCCESS;
}