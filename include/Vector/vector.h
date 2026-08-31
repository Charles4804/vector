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
int VectorPush(Vector *v, const void *item);

__attribute__((deprecated("Use VectorPopFast"))) VECTOR_API 
int VectorPop(Vector *v, size_t index);

VECTOR_API
void VectorPopFast(Vector *v, size_t index);

VECTOR_API
int VectorPopByValue(Vector *v, const void *value, int string);

__attribute__((deprecated("Use VectorPopFast"))) VECTOR_API
int VectorPopUnsafe(Vector *v, size_t index);

__attribute__((deprecated("Use VectorPopRangeFast"))) VECTOR_API 
int VectorPopRange(Vector *v, size_t a, size_t b);

VECTOR_API
void VectorPopRangeFast(Vector *v, size_t a, size_t b);

__attribute__((deprecated("Use VectorPopRangeFast")))VECTOR_API
int VectorPopRangeUnsafe(Vector *v, size_t a, size_t b);

VECTOR_API
int VectorValueExists(Vector *v, const void *value, int string);

VECTOR_API
int VectorInsert(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorInsertUnsafe(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorAddRange(Vector *dest ,Vector *v);

VECTOR_API
void *VectorGet(Vector *v, size_t index);

VECTOR_API
void *VectorGetByValue(Vector *v, const void *value, int string); 

VECTOR_API
void VectorReplace(Vector *v, size_t index, const void *value);

VECTOR_API 
size_t VectorGetCount(Vector *v); 

VECTOR_API
size_t VectorGetCapacity(Vector *v); 

VECTOR_API
size_t VectorGetIndexByValue(Vector *v, const void *value, int string);

VECTOR_API
void VectorClear(Vector *v);

VECTOR_API
void VectorFree(Vector *v);

#endif
