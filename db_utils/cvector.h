#ifndef RANDOM_TEXT_GENERATOR_CVECTOR_H
#define RANDOM_TEXT_GENERATOR_CVECTOR_H


#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CVECTOR_INIT_CAPACITY 4

typedef struct {
    void **data;
    int size, capacity;
    size_t element_size;
} cvector;

cvector *cvector_init(size_t n, size_t dataSize);

cvector *cvector_init2D(size_t n, size_t m, size_t dataSize);

int cvector_size(cvector *v);

void cvector_push(cvector *v, void *data);

int cvector_set(cvector *v, int index, void *data);

int cvector_delete(cvector *v, int index);

void *cvector_get(cvector *v, int index);

void cvector_clear(cvector *v);

void cvector_resize(cvector *v, int newCap);

void cvector_scanf(const char *format, void *a);

#endif //RANDOM_TEXT_GENERATOR_CVECTOR_H
