#include "cvector.h"

cvector *cvector_init(size_t n, size_t dataSize) {
    cvector *v = NULL;
    v->capacity = n;
    v->size = 0;
    v->element_size = dataSize;
    v->data = (void **) malloc(CVECTOR_INIT_CAPACITY * sizeof(void *));
    return v;
}

int cvector_size(cvector *v) {
    return v->size;
}

void cvector_push(cvector *v, void *data) {
    if (v->size >= v->capacity) {
        cvector_resize(v, v->capacity * 2);
    }
    v->data[v->size] = (void *)malloc(v->element_size);
    memcpy(v->data[v->size], data, v->element_size);
}

int cvector_set(cvector *v, int index, void *data) {
    if (index >= 0 && index < v->size) {
        memcpy(v->data[index], data, v->element_size);
        return 1;
    }
    return 0;
}

int cvector_delete(cvector *v, int index) {
    if (index < 0 || index > v->size - 1 || v->size <= 0) {
        return 0;
    }
    free(cvector_get(v, index));
    for (int i = index; i < v->size - 1; ++i) {
        v->data[i] = v->data[i + 1];
    }
    cvector_resize(v, v->size - 1);
    v->size--;
    return 1;
}

void *cvector_get(cvector *v, int index) {
    if (index < 0 || index > v->size - 1 || v->size <= 0) {
        return NULL;
    }
    return v->data[index];
}

void cvector_clear(cvector *v) {
    for (int i = 0; i < v->size; ++i) {
        free(v->data[i]);
        v->size = 0;
        free(v->data);
    }
}

void cvector_resize(cvector *v, int newCap) {
    v->capacity = newCap;
    v->data = realloc(v->data, newCap * sizeof(void *));
}

void cvector_fscanf(FILE *stream, const char *format, cvector *v) {
    fscanf(stream, format, &v);
}
