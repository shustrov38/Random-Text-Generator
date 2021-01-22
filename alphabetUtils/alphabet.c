#include "alphabet.h"

static char **alphabet;

void createAlphabet() {
    FILE *letterChangeFile = fopen("../alphabetUtils/alphabet.txt", "r");
    alphabet = createArray2D();
    for (int i = 0; i < 29; ++i) {
        fgets(alphabet[i], 10, letterChangeFile);
    }
    fclose(letterChangeFile);
}

int isUpper(const char *word) {
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][0]) {
            return 1;
        }
    }
    return 0;
}

void setLower(char *word) {
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][0]) {
            word[0] = alphabet[i][1];
            return;
        }
    }
}

void setUpper(char *word) {
    for (int i = 0; i < 29; ++i) {
        if (word[0] == alphabet[i][1]) {
            word[0] = alphabet[i][0];
            return;
        }
    }
}