#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "db_utils/database.h"

#define SENTENCE_LENGTH 100
#define CHANCE_FOR_PHRASE 30

char *getSentence(TemplateDictionary *dict, char *action) {
    char *result = (char *) malloc(SENTENCE_LENGTH * sizeof(char));
    strcat(result, getRandomValueFromTemplateDictionary(dict, action, PREFIX));
    strcat(result, " ");
    strcat(result, getRandomValueFromTemplateDictionary(dict, action, SUFFIX));
    strcat(result, ". ");
    if (rand() % 101 <= CHANCE_FOR_PHRASE) {
        strcat(result, getRandomValueFromTemplateDictionary(dict, action, POSTFIX));
        strcat(result, ". ");
    }
    return result;
}

int main() {
    unsigned seed = time(0);
    rand();
    srand(seed);

    setlocale(LC_ALL, "Russian");

    TemplateDictionary *dict = createTemplateDictionary();
    loadTemplateDictionary("../db_utils/database.txt", dict, 0);

    char *action = "старт";
    for (int i = 0; i < 10; ++i) {
        printf("\n%s", getSentence(dict, action));
    }

    return EXIT_SUCCESS;
}
