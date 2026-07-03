#include "vector/vector.h"

void VectorNew(Vector *v, size_t item_size)
{
    v->item_size = item_size;
    v->count = 0;
    v->capacity = 2;
    v->data = (void *)malloc(v->capacity * v->item_size);
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
    if (index > v->count)
    {
        return 1;
    }
    if (index == v->count)
    {
        v->count--;
    }
    else
    {
        char *current;
        char *ahead;
        for (size_t i = index; i < v->count; i++)
        {
            current = (char *)v->data + (i * v->item_size);
            ahead = (char *)v->data + ((i + 1) * v->item_size);
            memmove(current, ahead, v->item_size);
        }
        v->count--;
    }
}

int VectorPopByValue(Vector *v, const void *value, int string)
{
    if (string)
    {
        int found = 0;
        for (size_t i = 0; i < v->count; i++)
        {
            char *target_addr = (char *)v->data + (i * v->item_size);
            char *ahead;

            char *s1 = target_addr;
            char *s2 = (char *)value;
            
            while (!found && *s1 && (*s1 == *s2))
            {
                s1++;
                s2++;
            }
            if (!found && *s1 == '\0' && *s2 == '\0')
            {
                found = 1;
                if (i == v->count)
                {
                    v->count--;
                    break;
                }
                i = 0;
            }
            else if (found)
            {
                ahead = (char *)v->data + ((i + 1) * v->item_size);
                memmove(target_addr, ahead, v->item_size);
            }
        }
        v->count--;
    }
    else 
    {
        int found = 0;
        for (size_t i = 0; i < v->count; i++)
        {
            char *target_addr = (char *)v->data + (i * v->item_size);
            char *ahead;
            if (!found && memcmp(target_addr, value, v->item_size) == 0)
            {
                found = 1;
                if (i == v->count)
                {
                    v->count--;
                    break;
                }
                i = 0;
            }
            else if (found)
            {
                ahead = (char *)v->data + ((i + 1) * v->item_size);
                memmove(target_addr, ahead, v->item_size);
            }
        }
        v->count--;
    }
}

void *VectorGet(Vector *v, size_t index)
{
    return (void *)((char *)v->data + (index * v->item_size));
}


void *VectorGetByValue(Vector *v, const void *value, int string)
{
    if (string)
    {
        for (size_t i = 0; i < v->count; i++)
        {
            char *target_addr = (char *)v->data + (i * v->item_size);
            char *s1 = target_addr;
            char *s2 = (char *)value;
            
            while (*s1 && (*s1 == *s2))
            {
                s1++;
                s2++;
            }

            if (*s1 == '\0' && *s2 == '\0')
            {
                return (void *)target_addr;
            }
        }
        return nullptr;   
    }   
    else
    {
        for (size_t i = 0; i < v->count; i++)
        {
            char *target_addr = (char *)v->data + (i * v->item_size);
            if (memcmp(target_addr, value, v->item_size) == 0)
            {
                return (void *)target_addr;
            }
        }
        return nullptr;
    }
}

size_t VectorGetCount(Vector *v)
{
    return v->count;
}

size_t VectorGetCapacity(Vector *v)
{
    return v->capacity;
}

size_t VectorGetIndexByName(Vector *v, const char *name)
{
    for (size_t i = 0; i < v->count; i++)
    {
        char *target_addr = (char *)v->data + (i * v->item_size);
        char *s1 = target_addr;
        char *s2 = (char *)name;

        while (*s1 && (*s1 == *s2))
        {
            s1++;
            s2++;
        }

        if (*s1 == '\0' && *s2 == '\0')
        {
            return i;
        }
    }
    return 1;    
}

void VectorFree(Vector *v)
{
    v->item_size = 0;
    v->count = 0;
    v->capacity = 0;
    free(v->data);
}
