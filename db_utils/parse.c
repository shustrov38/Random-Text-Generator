#include "parse.h"

char **createArray2D() {
    char **t = (char **) malloc(sizeof(char *) * MAX_ARR_LEN);
    for (int i = 0; i < MAX_ARR_LEN; ++i) {
        t[i] = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    }
    return t;
}

int parse(char *filename, Dict *dict) {
    FILE *in = fopen(filename, "r");

    char *action = (char *) malloc(sizeof(char) * MAX_STR_LEN);

    int prefixSize = 0, suffixSize = 0, postfixSize = 0;

    char **prefix = createArray2D();
    char **suffix = createArray2D();
    char **postfix = createArray2D();

    while (!feof(in)) {
        fscanf(in, "#%s", action);

        char check[MAX_STR_LEN];

        fscanf(in, "%*s");
        while (1) {
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0) {
                break;
            } else {
                strcpy(prefix[prefixSize], check);
                prefixSize++;
            }
        }

        fscanf(in, "%*s");
        while (1) {
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0) {
                break;
            } else {
                strcpy(suffix[suffixSize], check);
                suffixSize++;
            }
        }

        fscanf(in, "%*s");
        while (1) {
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0) {
                break;
            } else {
                strcpy(postfix[postfixSize], check);
                postfixSize++;
            }

        }
    }

    initSpecificKey(dict, action);
    int result = updateData(dict, action, prefix, prefixSize, suffix, suffixSize, postfix, postfixSize);
    printCollectedData(dict, action);

//    printf("%s\n", action);
//    printf("Pref %d Suf %d Postf %d\n", prefixSize, suffixSize, postfixSize);
//    for (int i = 0; i < prefixSize; ++i){
//        printf("%s ", prefix[i]);
//    } printf("\n");
//
//    for (int i = 0; i < suffixSize; ++i){
//        printf("%s ", suffix[i]);
//    } printf("\n");
//
//    for (int i = 0; i < postfixSize; ++i){
//        printf("%s ", postfix[i]);
//    } printf("\n");

    return result;
}
