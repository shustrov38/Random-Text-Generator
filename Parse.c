#include "Parse.h"
#include "database.h"
#include <string.h>
#include <stdio.h>

FILE *in;

char **createArr() {
    char **t = (char **) malloc(sizeof(char *) * MAX_STR_LEN);
    for (int i = 0; i < MAX_STR_LEN; ++i) {
        t[i] = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    }
    return t;
}

void parse(Dict *dict) {
    in = fopen("../DataBase.txt", "r");

    char *action = (char *) malloc(sizeof(char) * MAX_STR_LEN);

    int prefCount = 0;
    int sufCount = 0;
    int postCount = 0;

    char **prefix = createArr();
    char **suffix = createArr();
    char **postfix = createArr();

    while (!feof(in)) {
        fscanf(in, "#%s", action);

        char check[MAX_STR_LEN];

        fscanf(in, "%*s");
        while (1){
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0){
                break;
            } else {
                strcpy(prefix[prefCount], check);
                prefCount++;
            }
        }

        fscanf(in, "%*s");
        while (1){
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0){
                break;
            } else {
                strcpy(suffix[sufCount], check);
                sufCount++;
            }
        }

        fscanf(in, "%*s");
        while (1){
            fscanf(in, "%s", check);
            if (strcmp(check, "--") == 0){
                break;
            } else {
                strcpy(postfix[postCount], check);
                postCount++;
            }

        }
    }

    //initSpecificKey(dict, action);

    //printCollectedData(dict, action);

    printf("%s\n", action);
    printf("Pref %d Suf %d Postf %d\n", prefCount, sufCount, postCount);
    for (int i = 0; i < prefCount; ++i){
        printf("%s ", prefix[i]);
    } printf("\n");

    for (int i = 0; i < sufCount; ++i){
        printf("%s ", suffix[i]);
    } printf("\n");

    for (int i = 0; i < postCount; ++i){
        printf("%s ", postfix[i]);
    } printf("\n");

}
