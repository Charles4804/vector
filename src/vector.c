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
    if ((v->data = (void *)malloc(v->capacity * v->item_size)) == NULL)
    {
        return 1;
    }
    return 0;
}

int VectorAdd(Vector *v, const void *item)
{
    if (v->count == v->capacity)
    {
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    memcpy((char *)v->data + (v->count * v->item_size), item, v->item_size);
    v->count++;
    return 0;
}

int VectorRemoveAt(Vector *v, size_t index)
{
    if (index >= v->count)
    {
        return 1;
    }
    char *target_addr = (char *)v->data + (v->item_size * index);
    memmove(target_addr, target_addr + v->item_size, v->item_size * ((v->count - (index + 1))));
    v->count--;
    return 0;
}

void _VectorRemoveAt(Vector *v, size_t index)
{
    char *target_addr = (char *)v->data + (v->item_size * index);
    memmove(target_addr, target_addr + v->item_size, v->item_size * ((v->count - (index + 1))));
    v->count--;
}

int __VectorRemove(Vector *v, const void *value, int p)
{
    char *dest;
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, (char *)value))
            {
                dest = (char *)v->data + (v->item_size * i);

                memmove(dest, dest + v->item_size, v->item_size * (v->count - (i + 1))); 
                v->count--;
                return 0;
            }
        }      
        return 1;
    }
    for (size_t i = 0; i < v->count; i++)
    {
        dest = (char *)v->data + (v->item_size * i);
        if (!memcmp(dest, value, v->item_size))
        {
            memmove(dest, dest + v->item_size, v->item_size * (v->count - (i + 1)));
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
    memmove((char *)v->data + (v->item_size * a), (char *)v->data + (v->item_size * (b + 1)), v->item_size * (v->count - (b + 1)));
    
    v->count -= (b - a) + 1;
    return 0;
}

void _VectorRemoveRange(Vector *v, size_t a, size_t b)
{
    memmove((char *)v->data + (v->item_size * a), (char *)v->data + (v->item_size * (b + 1)), v->item_size * (v->count - (b + 1)));
    v->count -= (b - a) + 1;
}

int __VectorContains(Vector *v, const void *value, int p)
{
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, (char *)value))
            {
                return 0;
            }
        }      
        return 1;
    }
    char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = (char *)v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
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
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    char *target_addr = (char *)v->data + (v->item_size * (index + 1));
    char *src_addr = (char *)v->data + (v->item_size * index);
    memmove(target_addr, src_addr, v->item_size * (v->count - index));
    memcpy(src_addr, value, v->item_size);

    v->count++;
    return 0;    
}

int _VectorInsert(Vector *v, size_t index, const void *value)
{
    if ((v->count + 1) >= v->capacity)
    {
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == NULL)
        {
            return 1;
        }
        v->data = tmp;
    }
    char *target_addr = (char *)v->data + (v->item_size * (index + 1));
    char *src_addr = (char *)v->data + (v->item_size * index);
    memmove(target_addr, src_addr, v->item_size * (v->count - index));
    memcpy(src_addr, value, v->item_size);

    v->count++;
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
        void *tmp;
        if ((tmp = realloc(dest->data, dest->capacity * dest->item_size)) == NULL)
        {
            return 1;
        }
        dest->data = tmp;
    }
    memcpy((char *)dest->data + (dest->item_size * dest->count), v->data, v->item_size * v->count);
    dest->count += v->count;
    return 0;
}

int VectorEnsureCapacity(Vector *v, size_t capacity)
{
    if (v->capacity < capacity)
    {
        while (v->capacity < capacity)
        {
            v->capacity <<= 1;
        }
        void *tmp;
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
    return (void *)((char *)v->data + (index * v->item_size));
}

void *__VectorGet(Vector *v, const void *value, int p)
{
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, *(char **)value))
            {
                return (void *)((char *)v->data + (v->item_size * i));
            }
        }      
        return NULL;
    }
    char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = (char *)v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
        {
            return (void *)((char *)v->data + (v->item_size * i));     
        }
    }
    return NULL;
}

void *VectorGetData(Vector *v)
{
    return v->data;
}

int VectorReplace(Vector *v, size_t index, const void *value)
{
    if (index >= v->count)
    {
        return 1;
    }
    memcpy((char *)v->data + (index * v->item_size), value, v->item_size);   
    return 0;
}

void _VectorReplace(Vector *v, size_t index, const void *value)
{
    memcpy((char *)v->data + (index * v->item_size), value, v->item_size);
}

int VectorCopyTo(Vector *restrict v, size_t index, void *restrict array)
{
    if (index >= v->count)
    {
        return 1;
    }
    char *target_addr = (char *)v->data + (v->item_size * index);
    memcpy(array, target_addr, v->item_size * (v->count - index));
    return 0;
}

void VectorCopy(Vector *restrict v, void *restrict array)
{
    memcpy(array, v->data, v->item_size * v->count);
}

size_t __VectorGetIndex(Vector *v, const void *value, int p)
{
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, (char *)value))
            {
                return i;
            }
        }      
        return -1;
    }
    char *target_addr;
    for (size_t i = 0; i < v->count; i++)
    {
        target_addr = (char *)v->data + (v->item_size * i);
        if (!memcmp(target_addr, value, v->item_size))
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
