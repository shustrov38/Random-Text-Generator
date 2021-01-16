#include "Parse.h"
#include "database.h"
#include <string.h>
#include <stdio.h>

FILE *in;

void parse(){
    in = fopen("../DataBase.txt", "r");

    char action[MAX_STR_LEN];

    int PrefCount;
    int SufCount;
    int PostCount;

    char prefix[MAX_STR_LEN][MAX_STR_LEN];
    char suffix[MAX_STR_LEN][MAX_STR_LEN];
    char postfix[MAX_STR_LEN][MAX_STR_LEN];

    while (!feof(in)) {
        fscanf(in, "#%s", action);

        char trash[MAX_STR_LEN];

        fscanf(in, "%s %d", trash, &PrefCount);
        for (int i = 0; i < PrefCount; ++i){
            fscanf(in, "%s", prefix[i]);
        }

        fscanf(in, "%s %d",trash, &SufCount);
        for (int i = 0; i < SufCount; ++i){
            fscanf(in, "%s", suffix[i]);
        }

        fscanf(in, "%s %d", trash, &PostCount);
        for (int i = 0; i < PostCount; ++i){
            fscanf(in, "%s", postfix[i]);
        }
    }

    printf("Pref %d Suf %d  Postf %d\n", PrefCount, SufCount, PostCount);
    for (int i = 0; i < PrefCount; ++i){
        printf("%s ", prefix[i]);
    } printf("\n");

    for (int i = 0; i < SufCount; ++i){
        printf("%s ", suffix[i]);
    } printf("\n");

    for (int i = 0; i < PostCount; ++i){
        printf("%s ", postfix[i]);
    } printf("\n");
}
