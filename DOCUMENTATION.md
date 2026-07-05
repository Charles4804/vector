# VECTOR : DOCUMENTATION
**Table of Contents**
- [About](#name)
- [Synopsis](#synopsis)

## NAME
vector - dynamic array library

## DESCRIPTION
A C Library that provides a dynamic array.

## SYNOPSIS
```c
#include "vector/vector.h"

typedef struct
{
    void *data;
    size_t count;
    size_t capacity;
    size_t item_size;
} Vector;

void VectorNew(Vector *v, size_t item_size);

int VectorPush(Vector *v, const void *item);

int VectorPop(Vector *v, size_t index);

int VectorPopByValue(Vector *v, const void *value, int string);

void *VectorGet(Vector *v, size_t index);

void *VectorGetByValue(Vector *v, const void *value, int string); 

size_t VectorGetCount(Vector *v);

size_t VectorGetCapacity(Vector *v);

size_t VectorGetIndexByValue(Vector *v, const void *value, int string);

void VectorFree(Vector *v);
```

|FUNCTION|DESCRIPTION|
|--------|-----------|
|VectorNew|Initializes Vector|
|VectorPush|Pushes item to the end of the array, returns 1 if failed, otherwise 0|
|VectorPop|Moves right side to its left side, if index is at the end it jsut subtract count by one|
|VectorPopByValue|It does exactly what VectorPop do, but it looks for an index with the corresponding value|
|VectorGet|Returns void * to the memory address of the index|
|VectorGetByValue|Does exactly the same as Vector get but it looks for an index that has the specific value|
|VectorGetCount|Returns the current count of elements in the array|
|VectorGetCapacity|Returns the capacity of the array|
|VectorGetIndexByValue|Looks for the index of the specific value|
|VectorFree|Resets all the fields to their default. CRUCIAL|
