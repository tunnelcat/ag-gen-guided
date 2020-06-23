//
// Created by Kyle Cook on 6/11/18.
//

#include "vector.h"

void vectorInit(struct vector *vec) {
    vec->size = 0;
    vec->capacity = VECTOR_INITIAL_CAPACITY;
    vec->data = calloc(1, sizeof(void*)*VECTOR_INITIAL_CAPACITY);
}

void *vectorGet(struct vector *vec, int idx) {
    if(idx < vec->size) {
        return vec->data[idx];
    } else {
        return NULL;
    }
}

void vectorDoubleSize(struct vector *vec) {
    vec->data = realloc(vec->data, vec->capacity*2);
}

void vectorSet(struct vector *vec, int idx, void *data) {
    vec->data[idx] = data;
}

void vectorFree(struct vector *vec) {
    free(vec);
}
