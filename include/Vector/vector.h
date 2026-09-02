#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#define VECTOR_API __attribute__((visibility("default")))

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ||||||||||||||||||||||||||||||||||||||||||
//   _    ________________________  ____  |||
//  | |  / / ____/ ____/_  __/ __ \/ __ \ |||
//  | | / / __/ / /     / / / / / / /_/ / |||
//  | |/ / /___/ /___  / / / /_/ / _, _/  |||
//  |___/_____/\____/ /_/  \____/_/ |_|   |||  
//   --by Charles4804                     |||
//   ---protected by MIT license          |||


typedef struct
{
    void *data;
    size_t count;
    size_t capacity;
    size_t item_size;
} Vector;

VECTOR_API
int VectorNew(Vector *v, size_t item_size);

VECTOR_API
int VectorAdd(Vector *v, const void *item);

VECTOR_API
void VectorRemoveAt(Vector *v, size_t index);

VECTOR_API
int VectorRemove(Vector *v, const void *value, int string);

VECTOR_API
void VectorRemoveRange(Vector *v, size_t a, size_t b);

VECTOR_API
int VectorContains(Vector *v, const void *value, int string);

VECTOR_API
int VectorInsert(Vector *v, size_t index, const void *value);

VECTOR_API
int _VectorInsert(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorAddRange(Vector *dest ,Vector *v);

VECTOR_API
int VectorEnsureCapacity(Vector *v, size_t capacity);

VECTOR_API
void *VectorGetAt(Vector *v, size_t index);

VECTOR_API
void *VectorGet(Vector *v, const void *value, int p); 

VECTOR_API
void *VectorGetData(Vector *v);

VECTOR_API
void VectorReplace(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorCopyTo(Vector *v, size_t index, void *array);

VECTOR_API
void VectorCopy(Vector *v, void *array);

VECTOR_API
size_t VectorGetIndex(Vector *v, const void *value, int string);

VECTOR_API
void VectorClear(Vector *v);

VECTOR_API
void VectorFree(Vector *v);

#endif
