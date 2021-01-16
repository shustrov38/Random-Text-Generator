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

    int PrefCount;
    int SufCount;
    int PostCount;

    char **prefix = createArr();
    char **suffix = createArr();
    char **postfix = createArr();

    while (!feof(in)) {
        fscanf(in, "#%s", action);

        char trash[MAX_STR_LEN];

        fscanf(in, "%s %d", trash, &PrefCount);
        for (int i = 0; i < PrefCount; ++i) {
            fscanf(in, "%s", prefix[i]);
        }

        fscanf(in, "%s %d", trash, &SufCount);
        for (int i = 0; i < SufCount; ++i) {
            fscanf(in, "%s", suffix[i]);
        }

        fscanf(in, "%s %d", trash, &PostCount);
        for (int i = 0; i < PostCount; ++i) {
            fscanf(in, "%s", postfix[i]);
        }
    }

    initSpecificKey(dict, action);
    //printf("%s", dict->data[0]->key);
    //updatePrefix(dict, action, prefix, PrefCount);
    //updateSuffix(dict, action, suffix, SufCount);
    //updatePostfix(dict, action, postfix, PostCount);

    printCollectedData(dict, action);

//    printf("%s\n", action);
//    printf("Pref %d Suf %d Postf %d\n", PrefCount, SufCount, PostCount);
//    for (int i = 0; i < PrefCount; ++i){
//        printf("%s ", prefix[i]);
//    } printf("\n");
//
//    for (int i = 0; i < SufCount; ++i){
//        printf("%s ", suffix[i]);
//    } printf("\n");
//
//    for (int i = 0; i < PostCount; ++i){
//        printf("%s ", postfix[i]);
//    } printf("\n");

}
