#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

/*
 ||||||||||||||||||||||||||||||||||||||||||
   _    ________________________  ____  |||
  | |  / / ____/ ____/_  __/ __ \/ __ \ |||
  | | / / __/ / /     / / / / / / /_/ / |||
  | |/ / /___/ /___  / / / /_/ / _, _/  |||
  |___/_____/\____/ /_/  \____/_/ |_|   |||  
   --by Charles4804                     |||
   ---protected under MIT license       |||
*/

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

typedef struct
{
    unsigned char *restrict data;
    size_t count;
    size_t capacity;
    size_t item_size;
} Vector;

/** Selects the string or byte-wise lookup for VectorGet based on value's type */
#define VectorGet(v, value) _Generic((__typeof__(value)){0}, \
                                     const char *: __VectorGetStr, \
                                     char *: __VectorGetStr, \
                                     default: __VectorGet \
)(v, value)

/** Selects the string or byte-wise index lookup based on value's type */
#define VectorGetIndex(v, value) _Generic((__typeof__(value)){0}, \
                                          const char *: __VectorGetIndexStr, \
                                          char *: __VectorGetIndexStr, \
                                          default: __VectorGetIndex \
)(v, value)

/** Selects string comparison for char pointers, otherwise byte-wise comparison */
#define VectorContains(v, value) _Generic((__typeof__(value)){0}, \
                                          const char *: __VectorContainsStr, \
                                          char *: __VectorContainsStr, \
                                          default: __VectorContains \
)(v, value)

/** Selects string removal for char pointers, otherwise byte-wise removal */
#define VectorRemove(v, value) _Generic((__typeof__(value)){0}, \
                                        const char *: __VectorRemoveStr, \
                                        char *: __VectorRemoveStr, \
                                        default: __VectorRemove \
)(v, value)

/**
 * @brief Initializes a vector with an initial capacity of two items.
 *
 * Sets `item_size`, resets `count` to zero, sets `capacity` to two, and
 * allocates storage for the vector. If allocation fails, `data` is NULL and
 * the function returns 1.
 *
 * @param v Pointer to the vector to initialize; must point to a writable Vector.
 * @param item_size Size in bytes of each item.
 * @return 0 if allocation succeeds; 1 if allocation fails.
 */
VECTOR_API int VectorNew(Vector *v, size_t item_size);

/**
 * @brief Appends one item to the vector.
 * @param v Initialized vector to modify.
 * @param item Address of at least item_size bytes to copy into the vector.
 * @return 0 on success; 1 if growing the allocation fails.
 */
VECTOR_API int VectorAdd(Vector *v, const void *item);

/**
 * @brief Removes the item at index and shifts later items left.
 * @param v Initialized vector to modify.
 * @param index Index of the item to remove.
 * @return 0 if removed; 1 if index is outside the vector.
 */
VECTOR_API int VectorRemoveAt(Vector *v, size_t index);

/**
 * @brief Removes the item at index and shifts later items left, without bounds checking.
 * @param v Vector to modify.
 * @param index Index to remove; must be less than count.
 */
VECTOR_API void _VectorRemoveAt(Vector *v, size_t index);

/**
 * @brief Removes the first item whose bytes match value.
 * @param v Vector to search and modify.
 * @param value Address of item_size bytes to compare.
 * @return 0 if an item was removed; 1 if no item matched.
 */
VECTOR_API int __VectorRemove(Vector *v, const void *value);

/**
 * @brief Removes the first item containing a string equal to value.
 *
 * Items must be stored as char pointers; strings are compared with strcmp.
 * @param v Vector to search and modify.
 * @param value String to compare against stored strings.
 * @return 0 if an item was removed; 1 if no item matched.
 */
VECTOR_API int __VectorRemoveStr(Vector *v, const char *value);

/**
 * @brief Removes the inclusive index range [a, b], shifting later items left.
 * @param v Vector to modify.
 * @param a First index to remove.
 * @param b Last index to remove.
 * @return 0 on success; 1 if a > b or b is outside the vector.
 */
VECTOR_API int VectorRemoveRange(Vector *v, size_t a, size_t b);

/**
 * @brief Removes the inclusive index range [a, b] without bounds checking.
 * @param v Vector to modify.
 * @param a First index to remove; must not exceed b.
 * @param b Last index to remove; must be less than count.
 */
VECTOR_API void _VectorRemoveRange(Vector *v, size_t a, size_t b);

/**
 * @brief Tests whether an item with bytes equal to value exists.
 * @param v Vector to search.
 * @param value Address of item_size bytes to compare.
 * @return 0 if found; 1 if not found.
 */
VECTOR_API int __VectorContains(Vector *v, const void *value);

/**
 * @brief Tests whether an item contains a string equal to value.
 *
 * Items must be stored as char pointers; strings are compared with strcmp.
 * @param v Vector to search.
 * @param value String to search for.
 * @return 0 if found; 1 if not found.
 */
VECTOR_API int __VectorContainsStr(Vector *v, const char *value);

/**
 * @brief Inserts a copy of one item at index, shifting later items right.
 * @param v Vector to modify.
 * @param index Insertion position; count appends to the end.
 * @param value Address of item_size bytes to copy.
 * @return 0 on success; 1 if index is greater than count or growth fails.
 */
VECTOR_API int VectorInsert(Vector *v, size_t index, const void *value);

/**
 * @brief Inserts an item without checking that index is valid.
 * @param v Vector to modify.
 * @param index Insertion position; must be no greater than count.
 * @param value Address of item_size bytes to copy.
 * @return 0 on success; 1 if growing the allocation fails.
 */
VECTOR_API int _VectorInsert(Vector *v, size_t index, const void *value);

/**
 * @brief Inserts all items from src at index without validating index.
 * @param v Destination vector; must have the same item_size as src.
 * @param src Vector providing items.
 * @param index Insertion position; must be no greater than v->count.
 * @return 0 on success; 1 if growing the allocation fails.
 */
VECTOR_API int _VectorInsertRange(Vector *restrict v, Vector *restrict src, size_t index);

/**
 * @brief Inserts count items from array at index without validating index.
 * @param v Vector to modify.
 * @param array Source bytes containing count items.
 * @param index Insertion position; must be no greater than v->count.
 * @param count Number of items to insert.
 * @return 0 on success; 1 if growing the allocation fails.
 */
VECTOR_API int _VectorInsertRangeArray(Vector *restrict, void *restrict array, size_t index, size_t count);

/**
 * @brief Inserts all items from src at index, shifting existing items right.
 * @param v Destination vector; must have the same item_size as src.
 * @param src Vector providing items.
 * @param index Insertion position; count appends to the end.
 * @return 0 on success; 1 if index is greater than count or allocation fails.
 */
VECTOR_API int VectorInsertRange(Vector *restrict v, Vector *restrict src, size_t index);

/**
 * @brief Inserts count items from array at index.
 * @param v Vector to modify.
 * @param array Source bytes containing count items.
 * @param index Insertion position; count appends to the end.
 * @param count Number of items to insert.
 * @return 0 on success; 1 if index is greater than count or allocation fails.
 */
VECTOR_API int VectorInsertRangeArray(Vector *restrict v, void *restrict array, size_t index, size_t count);

/**
 * @brief Appends all items from v to dest.
 * @param dest Destination vector; item_size must match v->item_size.
 * @param v Vector providing items.
 * @return 0 on success; 1 if growing dest fails.
 */
VECTOR_API int VectorAddRange(Vector *restrict dest ,Vector *restrict v);

/**
 * @brief Appends items from array to v.
 * @param v Destination vector.
 * @param array Source bytes containing the items.
 * @param count Number of items to append.
 * @return 0 on success; 1 if growing v fails.
 */
VECTOR_API int VectorAddRangeArray(Vector *restrict v, void *restrict array, size_t count);

/**
 * @brief Reverses all items in a non-empty vector using a stack temporary buffer.
 * @param v Vector to reverse.
 */
VECTOR_API void VectorReverse(Vector *v);

/**
 * @brief Reverses the items in the half-open range [a, b).
 * @param v Vector to modify.
 * @param a First item index; the range must be non-empty and within the vector.
 * @param b One past the last item index; must be no greater than count.
 */
VECTOR_API void VectorReverseRange(Vector *v, size_t a, size_t b);

/**
 * @brief Reverses all items in a non-empty vector using byte-by-byte swaps.
 * @param v Vector to reverse.
 */
VECTOR_API void VectorReverseSafe(Vector *v);

/**
 * @brief Reverses the items in [a, b) using byte-by-byte swaps.
 * @param v Vector to modify.
 * @param a First item index; the range must be non-empty and within the vector.
 * @param b One past the last item index; must be no greater than count.
 */
VECTOR_API void VectorReverseRangeSafe(Vector *v, size_t a, size_t b);

/**
 * @brief Reverses all items using a temporary heap allocation.
 * @param v Non-empty vector to reverse.
 */
VECTOR_API int VectorReverseHeap(Vector *v);

/**
 * @brief Reverses [a, b) using a temporary heap allocation.
 * @param v Vector to modify.
 * @param a First item index; the range must be non-empty and within the vector.
 * @param b One past the last item index; must be no greater than count.
 */
VECTOR_API int VectorReverseRangeHeap(Vector *v, size_t a, size_t b);

/**
 * @brief Ensures capacity is at least the requested number of items.
 *
 * Capacity grows by doubling.
 * @param v Vector to grow.
 * @param capacity Minimum requested capacity in items.
 * @return 0 if capacity is sufficient or growth succeeds; 1 if realloc fails.
 */
VECTOR_API int VectorEnsureCapacity(Vector *v, size_t capacity);

/**
 * @brief Returns a pointer to the item at index.
 * @param v Vector to access.
 * @param index Item index.
 * @return Pointer to the item, or NULL if index is out of range.
 */
VECTOR_API void *VectorGetAt(Vector *v, size_t index);

/**
 * @brief Finds the first item whose bytes match value.
 * @param v Vector to search.
 * @param value Address of item_size bytes to compare.
 * @return Pointer to the matching item, or NULL if none matches.
 */
VECTOR_API void *__VectorGet(Vector *v, const void *value); 

/**
 * @brief Returns the first stored char-pointer slot whose string equals value.
 * @param v Vector containing char-pointer items.
 * @param value String to search for.
 * @return Pointer to the stored slot, or NULL if no string matches.
 */
VECTOR_API void *__VectorGetStr(Vector *v, const char *value);

/**
 * @brief Returns the vector's backing storage.
 * @param v Vector whose storage is requested.
 * @return Backing-storage pointer, invalidated by reallocation or VectorFree.
 */
VECTOR_API void *VectorGetData(Vector *v);

/**
 * @brief Replaces the item at index with a byte-for-byte copy of value.
 * @param v Vector to modify.
 * @param index Item index to replace.
 * @param value Address of item_size bytes to copy.
 * @return 0 on success; 1 if index is out of range.
 */
VECTOR_API int VectorReplace(Vector *v, size_t index, const void *value);

/**
 * @brief Replaces the item at index without bounds checking.
 * @param v Vector to modify.
 * @param index Item index; must be less than count.
 * @param value Address of item_size bytes to copy.
 */
VECTOR_API void _VectorReplace(Vector *v, size_t index, const void *value);

/**
 * @brief Copies items from index through the end into array.
 * @param v Source vector.
 * @param index First item to copy.
 * @param array Destination with room for (count - index) * item_size bytes.
 * @return 0 on success; 1 if index is outside the vector.
 */
VECTOR_API int VectorCopyTo(Vector *restrict v, size_t index, void *restrict array);

/**
 * @brief Copies all vector items into array.
 * @param v Source vector.
 * @param array Destination with room for count * item_size bytes.
 */
VECTOR_API void VectorCopy(Vector *restrict v, void *restrict array);

/**
 * @brief Finds the first item whose bytes match value.
 * @param v Vector to search.
 * @param value Address of item_size bytes to compare.
 * @return Matching index, or (size_t)-1 if absent.
 */
VECTOR_API size_t __VectorGetIndex(Vector *v, const void *value);

/**
 * @brief Finds the first stored char-pointer item whose string equals value.
 * @param v Vector containing char-pointer items.
 * @param value String to search for.
 * @return Matching index, or (size_t)-1 if absent.
 */
VECTOR_API size_t __VectorGetIndexStr(Vector *v, const char *value);

/** Sets the item count to zero without freeing storage. */
VECTOR_API void VectorClear(Vector *v);

/**
 * @brief Frees the backing storage and resets item_size, count, and capacity.
 * @param v Vector to release; its data member is not set to NULL afterward.
 */
VECTOR_API void VectorFree(Vector *v);

#endif
