#include "Vector/vector.h"

// ||||||||||||||||||||||||||||||||||||||||||
//   _    ________________________  ____  |||
//  | |  / / ____/ ____/_  __/ __ \/ __ \ |||
//  | | / / __/ / /     / / / / / / /_/ / |||
//  | |/ / /___/ /___  / / / /_/ / _, _/  |||
//  |___/_____/\____/ /_/  \____/_/ |_|   |||  
//   --by Charles4804                     |||
//   ---protected by MIT license          |||

int VectorNew(Vector *v, size_t item_size)
{
    v->item_size = item_size;
    v->count = 0;
    v->capacity = 2;
    if ((v->data = malloc(v->capacity * v->item_size)) == NULL)
    {
        return 1;
    }
    return 0;
}

int VectorAdd(Vector *v, const void *item)
{
    if (v->count == v->capacity)
    {
        unsigned char *tmp;
        v->capacity <<= 1;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    memcpy(v->data + (v->count * v->item_size), item, v->item_size);
    v->count++;
    return 0;
}

int VectorRemoveAt(Vector *v, size_t index)
{
    if (index >= v->count)
    {
        return 1;
    }
    unsigned char *target_addr = v->data + (v->item_size * index);
    memmove(target_addr, target_addr + v->item_size, v->item_size * ((v->count - (index + 1))));
    v->count--;
    return 0;
}

void _VectorRemoveAt(Vector *v, size_t index)
{
    unsigned char *target_addr = v->data + (v->item_size * index);
    memmove(target_addr, target_addr + v->item_size, v->item_size * ((v->count - (index + 1))));
    v->count--;
}

int __VectorRemove(Vector *v, const void *value)
{
    unsigned char *dest;
    for (size_t i = 0; i < v->count; i++)
    {
        dest = v->data + (v->item_size * i);
        if (!memcmp(dest, value, v->item_size))
        {
            memmove(dest, dest + v->item_size, v->item_size * (v->count - (i + 1)));
            v->count--;
            return 0;
        }
    }
    return 1;
}

int __VectorRemoveStr(Vector *v, const char *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!strcmp(*(char **)target_addr, value))
        {
            memmove(target_addr, target_addr + v->item_size, v->item_size * (v->count - (i + 1)));
            v->count--;
            return 0;
        }
    }
    return 1;
}

int VectorRemoveRange(Vector *v, size_t a, size_t b)
{
    if (a > b || b >= v->count)
    {
        return 1;
    }
    memmove(v->data + (v->item_size * a), v->data + (v->item_size * (b + 1)), v->item_size * (v->count - (b + 1)));
    
    v->count -= (b - a) + 1;
    return 0;
}

void _VectorRemoveRange(Vector *v, size_t a, size_t b)
{
    memmove(v->data + (v->item_size * a), v->data + (v->item_size * (b + 1)), v->item_size * (v->count - (b + 1)));
    v->count -= (b - a) + 1;
}

int __VectorContains(Vector *v, const void *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
        {
            return 0;
        }
    }
    return 1;
}

int __VectorContainsStr(Vector *v, const char *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!strcmp(*(char **)target_addr, value))
        {
            return 0;
        }
    }
    return 1;
}

int VectorInsert(Vector *v, size_t index, const void *value)
{
    if (index > v->count)
    {
        return 1;
    }
    if ((v->count + 1) >= v->capacity)
    {
        unsigned char *tmp;
        v->capacity <<= 1;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    unsigned char *target_addr = v->data + (v->item_size * (index + 1));
    unsigned char *src_addr = v->data + (v->item_size * index);
    memmove(target_addr, src_addr, v->item_size * (v->count - index));
    memcpy(src_addr, value, v->item_size);

    v->count++;
    return 0;    
}

int _VectorInsert(Vector *v, size_t index, const void *value)
{
    if ((v->count + 1) >= v->capacity)
    {
        unsigned char *tmp;
        v->capacity <<= 1;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    unsigned char *target_addr = v->data + (v->item_size * (index + 1));
    unsigned char *src_addr = v->data + (v->item_size * index);
    memmove(target_addr, src_addr, v->item_size * (v->count - index));
    memcpy(src_addr, value, v->item_size);

    v->count++;
    return 0;    
}

int _VectorInsertRange(Vector *restrict v, Vector *restrict src, size_t index)
{
    size_t x = v->count + src->count;
    if (x >= v->capacity)
    {
        while (v->capacity < x)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    unsigned char *s = v->data + (v->item_size * index);

    memmove(s + (v->item_size * src->count), s, v->item_size * (v->count - index));
    memcpy(s, src->data, v->item_size * src->count);
    v->count += src->count;
    return 0;
}

int _VectorInsertRangeArray(Vector *restrict v, void *restrict array, size_t index, size_t count)
{
    size_t x = v->count + count;
    if (x >= v->capacity)
    {
        while (v->capacity < x)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
    }
    unsigned char *s = v->data + (v->item_size * index);
    memmove(s + (v->item_size * count), s, v->item_size * (v->count - index));
    memcpy(s, array, v->item_size * count);
    v->count += count;
    return 0;
}


int VectorInsertRange(Vector *restrict v, Vector *restrict src, size_t index)
{
    if (index > v->count)
    {
        return 1;
    }
    size_t x = v->count + src->count;
    if (x >= v->capacity)
    {
        while (v->capacity < x)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    unsigned char *s = v->data + (v->item_size * index);

    memmove(s + (v->item_size * src->count), s, v->item_size * (v->count - index));
    memcpy(s, src->data, v->item_size * src->count);
    v->count += src->count;
    return 0;
}

int VectorInsertRangeArray(Vector *restrict v, void *restrict array, size_t index, size_t count)
{
    if (index > v->count)
    {
        return 1;
    }
    size_t x = v->count + count;
    if (x >= v->capacity)
    {
        while (v->capacity < x)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
    }
    unsigned char *s = v->data + (v->item_size * index);
    memmove(s + (v->item_size * count), s, v->item_size * (v->count - index));
    memcpy(s, array, v->item_size * count);
    v->count += count;
    return 0;
}

int VectorAddRange(Vector *restrict dest, Vector *restrict v)
{
    size_t x = dest->count + v->count;
    if (x >= dest->capacity)
    {
        while (dest->capacity < x)
        {
            dest->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(dest->data, dest->capacity * dest->item_size)) == NULL)
        {
            return 1;
        }
        dest->data = tmp;
    }
    memcpy(dest->data + (dest->item_size * dest->count), v->data, v->item_size * v->count);
    dest->count += v->count;
    return 0;
}

int VectorAddRangeArray(Vector *restrict v, void *restrict array, size_t count)
{
    size_t x = v->count + count;
    if (x >= v->capacity)
    {
        while (v->capacity < x)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    memcpy(v + (v->item_size * v->count), array, v->item_size * count);
    v->count += count;
    return 0;
}

void VectorReverse(Vector *v)
{
    unsigned char tmp[v->item_size];
    unsigned char *a = v->data;
    unsigned char *b = v->data + (v->item_size * (v->count - 1));

    while (a < b)
    {
        memcpy(tmp, a, v->item_size);
        memcpy(a, b, v->item_size);
        memcpy(b, tmp, v->item_size);

        a += v->item_size;
        b -= v->item_size;
    }
}

void VectorReverseRange(Vector *v, size_t a, size_t b)
{
    unsigned char tmp[v->item_size];
    unsigned char *aa = v->data + (v->item_size * a);
    unsigned char *bb = v->data + (v->item_size * (b - 1));
    
    while (a < b)
    {
        memcpy(tmp, aa, v->item_size);
        memcpy(aa, bb, v->item_size);
        memcpy(bb, tmp, v->item_size);

        a += v->item_size;
        b -= v->item_size;
    }
}

void VectorReverseSafe(Vector *v)
{
    unsigned char *a = v->data;
    unsigned char *b = v->data + (v->item_size * (v->count - 1));
    
    while (a < b)
    {
        for (size_t i = 0; i < v->item_size; i++)
        {
            unsigned char tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }
        a += v->item_size;
        b -= v->item_size;
    }
}

void VectorReverseRangeSafe(Vector *v, size_t a, size_t b)
{
    unsigned char *aa = v->data + (v->item_size * a);
    unsigned char *bb = v->data + (v->item_size * (b - 1));
    
    while (aa < bb)
    {
        for (size_t i = 0; i < v->item_size; i++)
        {
            unsigned char tmp = aa[i];
            aa[i] = bb[i];
            bb[i] = tmp;
        }
        aa += v->item_size;
        bb -= v->item_size;
    }
}

void VectorReverseHeap(Vector *v)
{
    unsigned *tmp = malloc(v->item_size);
    unsigned char *a = v->data;
    unsigned char *b = v->data + (v->item_size * (v->count - 1));
    
    while (a < b)
    {
        memcpy(tmp, a, v->item_size);
        memcpy(a, b, v->item_size);
        memcpy(b, tmp, v->item_size);
        a += v->item_size;
        b -= v->item_size;
    }
}

void VectorReverseRangeHeap(Vector *v, size_t a, size_t b)
{
    unsigned *tmp = malloc(v->item_size);
    unsigned char *aa = v->data + (v->item_size * a);
    unsigned char *bb = v->data + (v->item_size * (b - 1));
    
    while (aa < bb)
    {
        memcpy(tmp, aa, v->item_size);
        memcpy(aa, bb, v->item_size);
        memcpy(bb, tmp, v->item_size);
        aa += v->item_size;
        bb -= v->item_size;
    }
}

int VectorEnsureCapacity(Vector *v, size_t capacity)
{
    if (v->capacity < capacity)
    {
        while (v->capacity < capacity)
        {
            v->capacity <<= 1;
        }
        unsigned char *tmp;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    return 0;
}

void *VectorGetAt(Vector *v, size_t index)
{
    if (index >= v->count)
    {
        return NULL;
    }
    return (void *)(v->data + (index * v->item_size));
}

void *__VectorGet(Vector *v, const void *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
        {
            return (void *)(v->data + (v->item_size * i));     
        }
    }
    return NULL;
}

void *__VectorGetStr(Vector *v, const char *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!strcmp(*(char **)target_addr, value))
        {
            return (void *)target_addr;
        }
    }
    return NULL;
}

void *VectorGetData(Vector *v)
{
    return (void *)v->data;
}

int VectorReplace(Vector *v, size_t index, const void *value)
{
    if (index >= v->count)
    {
        return 1;
    }
    memcpy(v->data + (index * v->item_size), value, v->item_size);   
    return 0;
}

void _VectorReplace(Vector *v, size_t index, const void *value)
{
    memcpy(v->data + (index * v->item_size), value, v->item_size);
}

int VectorCopyTo(Vector *restrict v, size_t index, void *restrict array)
{
    if (index >= v->count)
    {
        return 1;
    }
    unsigned char *target_addr = v->data + (v->item_size * index);
    memcpy(array, target_addr, v->item_size * (v->count - index));
    return 0;
}

void VectorCopy(Vector *restrict v, void *restrict array)
{
    memcpy(array, v->data, v->item_size * v->count);
}

size_t __VectorGetIndex(Vector *v, const void *value)
{
    unsigned char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
        {
            return i;     
        }
    }
    return -1;
}

size_t __VectorGetIndexStr(Vector *v, const char *value)
{
    unsigned char *target_addr;

    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = v->data + (v->item_size * i);
        if (!strcmp(*(char **)target_addr, value))
        {
            return i;
        }
    }
    return -1;
}

void VectorClear(Vector *v)
{
    v->count = 0;
}

void VectorFree(Vector *v)
{
    v->item_size = 0;
    v->count = 0;
    v->capacity = 0;
    free(v->data);
}
