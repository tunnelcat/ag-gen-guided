//
// Created by Kyle Cook on 6/11/18.
//

#ifndef AG_GEN_VECTOR_H
#define AG_GEN_VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INITIAL_CAPACITY 64

#ifdef __cplusplus
extern "C" {
#endif

struct vector {
    size_t size;
    size_t capacity;
    void **data;
};

void vectorInit(struct vector *vec);
void *vectorGet(struct vector *vec, int idx);
void vectorDoubleSize(struct vector *vec);
void vectorSet(struct vector *vec, int idx, void *data);
void vectorFree(struct vector *vec);

#ifdef __cplusplus
}
#endif

#endif // AG_GEN_VECTOR_H
