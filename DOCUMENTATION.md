# VECTOR : DOCUMENTATION
**Table of Contents**
- [About](#name)
- [Synopsis](#synopsis)

## NAME
vector - dynamic array library

## DESCRIPTION
A C Library that provides a dynamic array.

## Synopsis
```c
#include "vector/vector.h"

typedef struct {
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
void VectorReplace(Vector *v, size_t index, const void *value);
int VectorInsert(Vector *v, size_t index, const void *value);
int VectorInsertUnsafe(Vector *v, size_t index, const void *value);
size_t VectorGetCount(Vector *v);
size_t VectorGetCapacity(Vector *v);
size_t VectorGetIndexByValue(Vector *v, const void *value, int string);
void VectorFree(Vector *v);
```

## Function Reference

| Function | Description |
| :--- | :--- |
| `VectorNew` | Initializes a new vector instance with a specified element size. |
| `VectorPush` | Appends an item to the end of the array; returns 0 on success, or 1 on failure. |
| `VectorPop` | Removes an item at the specified index and shifts subsequent elements left. |
| `VectorPopByValue` | Searches for a value, removes the first occurrence found, and shifts elements accordingly. |
| `VectorGet` | Retrieves a pointer to the element located at the specified index. |
| `VectorGetByValue` | Searches for the first index matching the provided value and returns a pointer to it. |
| `VectorGetCount` | Returns the number of elements currently stored in the vector. |
| `VectorReplace` | Replaces an index with a new value. |
|`VectorInsert` | Inserts an item to the specified index. |
|`VectorInsertUnsafe` | Inserts an item to the specifie index without checking if the index surpasses ++count < cap. |
| `VectorGetCapacity` | Returns the total number of elements the vector can currently hold before resizing. |
| `VectorGetIndexByValue` | Returns the index of the first occurrence of a specific value. |
| `VectorFree` | Deallocates internal memory and resets vector fields to default states. |
