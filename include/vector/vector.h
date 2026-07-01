#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#define VECTOR_API __attribute__((visibility("default")))

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct
{
    void *data;
    size_t count;
    size_t capacity;
    size_t item_size;
} Vector;

VECTOR_API
void VectorNew(Vector *v, size_t item_size);

VECTOR_API
void VectorPush(Vector *v, const void *item);

VECTOR_API
void VectorPop(Vector *v, size_t index);

VECTOR_API
void VectorPopByName(Vector *v, const char *name);

VECTOR_API
void *VectorGet(Vector *v, size_t index);

VECTOR_API
void *VectorGetByName(Vector *v, const char *name); // Only works if the memory address contains the string                                                     //directly

VECTOR_API
size_t VectorGetCount(Vector *v);

VECTOR_API
size_t VectorGetCapacity(Vector *v);

VECTOR_API
size_t VectorGetIndexByName(Vector *v, const char *name);

VECTOR_API
void VectorFree(Vector *v);

#endif
