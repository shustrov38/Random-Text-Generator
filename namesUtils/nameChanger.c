#include "nameChanger.h"

Name *names;
static int namesSize = 0, cap = 4;

void loadNames(int showDebug) {
    FILE *in = fopen("../namesUtils/names.txt", "r");

    names = (Name *) malloc(cap * sizeof(Name));
    int locSize = __NAMECHANGER_TAG_SIZE + __NAMECHANGER_NAME_SIZE * 3 + 6;

    while (!feof(in)) {
        char tag[4],
                first_name_gc[__NAMECHANGER_NAME_SIZE], second_name_gc[__NAMECHANGER_NAME_SIZE],
                first_name_dc[__NAMECHANGER_NAME_SIZE], second_name_dc[__NAMECHANGER_NAME_SIZE],
                first_name_nc[__NAMECHANGER_NAME_SIZE], second_name_nc[__NAMECHANGER_NAME_SIZE];

        char str[locSize];

        fgets(str, locSize, in);

        if (namesSize == cap) {
            cap *= 2;
            names = (Name *) realloc(names, cap * sizeof(Name));
        }

        sscanf(str, "%s ; %s %s ; %s %s ; %s %s", tag, first_name_nc, second_name_nc, first_name_gc, second_name_gc,
               first_name_dc, second_name_dc);

        strcpy(names[namesSize].tag, tag);

        strcpy(names[namesSize].first_name_nc, first_name_nc);
        strcpy(names[namesSize].second_name_nc, second_name_nc);

        strcpy(names[namesSize].first_name_gc, first_name_gc);
        strcpy(names[namesSize].second_name_gc, second_name_gc);

        strcpy(names[namesSize].first_name_dc, first_name_dc);
        strcpy(names[namesSize].second_name_dc, second_name_dc);


        namesSize++;
    }

    fclose(in);

    if (showDebug) {
        printf("[NAMES]\n");
        for (int i = 0; i < namesSize; ++i) {
            printf("tag: {%s}\n", names[i].tag);
            printf("\t[nc]%s %s\n", names[i].first_name_nc, names[i].second_name_nc);
            printf("\t[gc]%s %s\n", names[i].first_name_gc, names[i].second_name_gc);
            printf("\t[dc]%s %s\n", names[i].first_name_dc, names[i].second_name_dc);
        }
    }
}

static int find(char *tag) {
    for (int i = 0; i < namesSize; ++i) {
        if (!strcmp(names[i].tag, tag)) {
            return i;
        }
    }
    return -1;
}

char *getName(char *tag, int type) {
    int i = find(tag);

    if (i == -1) {
        return tag;
    }

    char *res = createArray1D();

    if (type == NAMES_GC) {
        if (rand() % 101 < __CHANCE_FOR_CAT) {
            strcat(res, names[i].first_name_gc);
            strcat(res, " ");
        }
        strcat(res, names[i].second_name_gc);
        freeArray1D(res);
        return res;
    }
    else if (type == NAMES_DC) {
        if (rand() % 101 < __CHANCE_FOR_CAT) {
            strcat(res, names[i].first_name_dc);
            strcat(res, " ");
        }
        strcat(res, names[i].second_name_dc);
        freeArray1D(res);
        return res;
    }
    else if (type == NAMES_NC) {
        if (rand() % 101 < __CHANCE_FOR_CAT) {
            strcat(res, names[i].first_name_nc);
            strcat(res, " ");
        }
        strcat(res, names[i].second_name_nc);
        freeArray1D(res);
        return res;
    }
    else {
        fprintf(stderr, "Bad type format in {getName}\n");
        exit(EXIT_FAILURE);
    }
}
