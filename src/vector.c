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
    if ((v->data = (void *)malloc(v->capacity * v->item_size)) == nullptr)
    {
        return 1;
    }
    return 0;
}

int VectorPush(Vector *v, const void *item)
{
    if (v->count == v->capacity)
    {
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == nullptr)
        {
            return 1;
        }
        v->data = tmp;
    }
    char *target_addr = (char *)v->data + (v->count * v->item_size);
    memcpy(target_addr, item, v->item_size);
    v->count++;
    return 0;
}

int VectorPop(Vector *v, size_t index)
{
    if (index >= v->count)
    {
        return 1;
    }
    if (index == (v->count - 1))
    {
        v->count--;
        return 0;
    }
    char *current;
    char *ahead;
    for (size_t i = index; i < v->count - 1; i++)
    {
        current = (char *)v->data + (i * v->item_size);
        ahead = (char *)v->data + ((i + 1) * v->item_size);
        memmove(current, ahead, v->item_size);
    }
    v->count--;
    return 0;
}

void VectorPopFast(Vector *v, size_t index)
{
    char *target_addr = (char *)v->data + (v->item_size * index);
    char *src_addr = (char *)v->data + (v->item_size * (index + 1));
    memmove(target_addr, src_addr, v->item_size * ((v->count - (index + 1))));
    v->count--;
}

int VectorPopByValue(Vector *v, const void *value, int p)
{
    char *src;
    char *dest;
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, *(char **)value))
            {
                dest = (char *)v->data + (v->item_size * i);
                src = (char *)v->data + (v->item_size * (i + 1));

                memmove(dest, src, v->item_size * (v->count - (i + 1))); // (v->count - i) - 1 = v->count - (i + 1)
                v->count--;
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
            dest = (char *)v->data + (v->item_size * i);
            src = (char *)v->data + (v->item_size * (i + 1));
            memmove(dest, src, v->item_size * (v->count - (i + 1)));
            v->count--;
            return 0;
        }
    }
    return 1;
}


int VectorPopUnsafe(Vector *v, size_t index)
{
    if (index == v->count)
    {
        v->count--;
        return 0;
    }
    else
    { 
        char *current;
        char *ahead;
        for (size_t i = index; i < v->count - 1; i++)
        {
            current = (char *)v->data + (i * v->item_size);
            ahead = (char *)v->data + ((i + 1) * v->item_size);
            memmove(current, ahead, v->item_size);
        }
        v->count--;
        return 0;
    }
    return 1;
   
}


int VectorPopRange(Vector *v ,size_t a, size_t b)
{
    if (a < 0 || a > v->capacity || b < 0 || b > v->count || a > b || b < a)
    {
        return 1;
    }
    size_t r = (b - a) + 1;
    if (b == v->count)
    {
        v->count -= r;
        return 0;
    }

    char *target_addr;
    char *src_addr;

    for (size_t q = a; b < v->count; q++)
    {
        target_addr = (char *)v->data + (q * v->item_size);
        b += 1;
        src_addr = (char *)v->data + (b * v->item_size);
        memmove(target_addr, src_addr, v->item_size);
    }
    v->count -= r;
    return 0;
}

void VectorPopRangeFast(Vector *v, size_t a, size_t b)
{
    size_t s = v->count - (b + 1);
    char *target_addr = (char *)v->data + (v->item_size * a);
    char *src_addr = (char *)v->data + (v->item_size * (b + 1));

    memmove(target_addr, src_addr, v->item_size * s);
    
    v->count -= (b - a) + 1;
}

int VectorPopRangeUnsafe(Vector *v ,size_t a, size_t b)
{
    size_t r = (b - a) + 1;

    if (b == v->count)
    {
        v->count -= r;
        return 0;
    }

    char *target_addr;
    char *src_addr;

    for (size_t i = a; b < v->count; i++)
    {
        target_addr = (char *)v->data + (i * v->item_size);
        b += 1;
        src_addr = (char *)v->data + (b * v->item_size);
        memmove(target_addr, src_addr, v->item_size);
    }
    v->count -= r;
    return 0;
}

int VectorValueExists(Vector *v, const void *value, int p)
{
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, *(char **)value))
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
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == nullptr)
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

int VectorInsertUnsafe(Vector *v, size_t index, const void *value)
{
    if ((v->count + 1) >= v->capacity)
    {
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == nullptr)
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

int VectorAddRange(Vector *dest, Vector *v)
{
    size_t x = dest->count + v->count;
    if (x >= dest->capacity)
    {
        size_t nc = dest->capacity;
        while (nc < x)
        {
            nc <<= 1;
        }
        dest->capacity = nc;
        void *tmp;
        if ((tmp = realloc(dest->data, dest->capacity * dest->item_size)) == nullptr)
        {
            return 1;
        }
        dest->data = tmp;
    }
    char *target_addr = (char *)dest->data + (dest->item_size * dest->count);
    memcpy(target_addr, v->data, v->item_size * v->count);
    dest->count += v->count;
    return 0;
}

void *VectorGet(Vector *v, size_t index)
{
    if (index >= v->count)
    {
        return nullptr;
    }
    return (void *)((char *)v->data + (index * v->item_size));
}

void *VectorGetByValue(Vector *v, const void *value, int p)
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
        return nullptr;
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
    return nullptr;
}

void VectorReplace(Vector *v, size_t index, const void *value)
{
    char *target_addr = (char *)v->data + (index * v->item_size);
    memcpy(target_addr, value, v->item_size);
}

size_t VectorGetCount(Vector *v)
{
    return v->count;
}

size_t VectorGetCapacity(Vector *v)
{
    return v->capacity;
}

size_t VectorGetIndexByValue(Vector *v, const void *value, int p)
{
    if (p)
    {
        char **target_addr;
        for (size_t i = 0; i < v->count; i++)
        {
            target_addr = (char **)((char *)v->data + (v->item_size * i));
            if (!strcmp(*target_addr, *(char **)value))
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
