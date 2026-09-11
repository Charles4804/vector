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
                                     const char *: __VectorGetStr, \
                                     char *: __VectorGetStr, \
                                     default: __VectorGet \
)(v, value)

#define VectorGetIndex(v, value) _Generic((__typeof__(value)){0}, \
                                          const char *: __VectorGetIndexStr, \
                                          char *: __VectorGetIndexStr, \
                                          default: __VectorGetIndex \
)(v, value)

#define VectorContains(v, value) _Generic((__typeof__(value)){0}, \
                                          const char *: __VectorContainsStr, \
                                          char *: __VectorContainsStr, \
                                          default: __VectorContains \
)(v, value)

#define VectorRemove(v, value) _Generic((__typeof__(value)){0}, \
                                        const char *: __VectorRemoveStr, \
                                        char *: __VectorRemoveStr, \
                                        default: __VectorRemove \
)(v, value)

VECTOR_API
int VectorNew(Vector *v, size_t item_size);

VECTOR_API
int VectorAdd(Vector *v, const void *item);

VECTOR_API
int VectorRemoveAt(Vector *v, size_t index);

VECTOR_API
void _VectorRemoveAt(Vector *v, size_t);

VECTOR_API
int __VectorRemove(Vector *v, const void *value);

VECTOR_API
int __VectorRemoveStr(Vector *v, const char *value);

VECTOR_API
int VectorRemoveRange(Vector *v, size_t a, size_t b);

VECTOR_API
void _VectorRemoveRange(Vector *v, size_t a, size_t b);

VECTOR_API
int __VectorContains(Vector *v, const void *value);

VECTOR_API
int __VectorContainsStr(Vector *v, const char *value);

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
void *__VectorGet(Vector *v, const void *value); 

VECTOR_API
void *__VectorGetStr(Vector *v, const char *value);

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
size_t __VectorGetIndex(Vector *v, const void *value);

VECTOR_API
size_t __VectorGetIndexStr(Vector *v, const char *value);

VECTOR_API
void VectorClear(Vector *v);

VECTOR_API
void VectorFree(Vector *v);

#endif
