#ifndef RANDOM_TEXT_GENERATOR_UTILITIES_H
#define RANDOM_TEXT_GENERATOR_UTILITIES_H


#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 1000
#define MAX_STRING_LENGTH 200

static char *createArray1D() {
    int n = MAX_STRING_LENGTH;
    char *t = (char *) malloc(n * sizeof(char));
    memset(t, 0, MAX_STRING_LENGTH);
    return t;
}

static char **createArray2D() {
    int n = MAX_ARRAY_LENGTH;
    char **t = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; ++i) {
        t[i] = createArray1D();
    }
    return t;
}

static void copyArray1D(char *dst, char *src) {
    int elementCount = MAX_STRING_LENGTH;
    memcpy(dst, src, elementCount * sizeof(char));
}

static void copyArray2D(char **dst, char **src) {
    int elementCount = MAX_ARRAY_LENGTH;
    for (int i = 0; i < elementCount; ++i) {
        copyArray1D(dst[i], src[i]);
    }
}

static void freeArray1D(char *t) {
    free(t);
}

static void freeArray2D(char **t) {
    size_t size = MAX_ARRAY_LENGTH;
    for (int i = 0; i < size; ++i) {
        freeArray1D(t[i]);
    }
    free(t);
}

static void freeBtfArray2D(char**t, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        freeArray1D(t[i]);
    }
    free(t);
}


#endif //RANDOM_TEXT_GENERATOR_UTILITIES_H
