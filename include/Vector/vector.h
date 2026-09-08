#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H


#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef WINDOWS_DLL
        #ifdef Vector_EXPORTS
            #define VECTOR_API __declspec(dllexport)
        #else
            #define VECTOR_API __declspec(dllimport)
        #endif
    #else
        #define VECTOR_API  
    #endif
#else
    #define VECTOR_API __attribute__((visibility("default")))
#endif

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
    void *restrict data;
    size_t count;
    size_t capacity;
    size_t item_size;
} Vector;

#define VectorGet(v, value) _Generic((__typeof__(value)){0}, \
                                     char *: __VectorGet((v), (value), 1), \
                                     default: __VectorGet((v), (value), 0) \
)

#define VectorGetIndex(v, value) _Generic((__typeof__(value)){0}, \
                                          char *: __VectorGetIndex((v), (value), 1), \
                                          default: __VectorGetIndex((v), (value), 0) \
)

#define VectorContains(v, value) _Generic((__typeof__(value)){0}, \
                                          char *: __VectorContains((v), (value), 1), \
                                          default: __VectorContains((v), (value), 0)\
)

#define VectorRemove(v, value) _Generic((__typeof__(value)){0}, \
                                        char *: __VectorRemove((v), (value), 1), \
                                        default: __VectorRemove((v), (value), 0) \
)

VECTOR_API
int VectorNew(Vector *v, size_t item_size);

VECTOR_API
int VectorAdd(Vector *v, const void *item);

VECTOR_API
int VectorRemoveAt(Vector *v, size_t index);

VECTOR_API
void _VectorRemoveAt(Vector *v, size_t);

VECTOR_API
int __VectorRemove(Vector *v, const void *value, int string);

VECTOR_API
int VectorRemoveRange(Vector *v, size_t a, size_t b);

VECTOR_API
void _VectorRemoveRange(Vector *v, size_t a, size_t b);

VECTOR_API
int __VectorContains(Vector *v, const void *value, int p);

VECTOR_API
int VectorInsert(Vector *v, size_t index, const void *value);

VECTOR_API
int _VectorInsert(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorAddRange(Vector *restrict dest ,Vector *restrict v);

VECTOR_API
int VectorEnsureCapacity(Vector *v, size_t capacity);

VECTOR_API
void *VectorGetAt(Vector *v, size_t index);

VECTOR_API
void *__VectorGet(Vector *v, const void *value, int p); 

VECTOR_API
void *VectorGetData(Vector *v);

VECTOR_API
int VectorReplace(Vector *v, size_t index, const void *value);

VECTOR_API
void _VectorReplace(Vector *v, size_t index, const void *value);

VECTOR_API
int VectorCopyTo(Vector *restrict v, size_t index, void *restrict array);

VECTOR_API
void VectorCopy(Vector *restrict v, void *restrict array);

VECTOR_API
size_t __VectorGetIndex(Vector *v, const void *value, int p);

VECTOR_API
void VectorClear(Vector *v);

VECTOR_API
void VectorFree(Vector *v);

#endif
