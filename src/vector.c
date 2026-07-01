#include "vector/vector.h"

void VectorNew(Vector *v, size_t item_size)
{
    v->item_size = item_size;
    v->count = 0;
    v->capacity = 2;
    v->data = (void *)malloc(v->capacity * v->item_size);
}

void VectorPush(Vector *v, const void *item)
{
    if (v->count == v->capacity)
    {
        void *tmp;
        v->capacity *= 2;
        if ((tmp = realloc(v->data, v->capacity * v->item_size)) == nullptr)
        {
            printf("VECTOR : ERROR CANNOT RESIZE DATA; function : 'VectorPush' line 11");
            exit(-1);
        }
        v->data = tmp;
    }
    char *target_addr = (char *)v->data + (v->count * v->item_size);
    memcpy(target_addr, item, v->item_size);
    v->count++;
}

void VectorPop(Vector *v, size_t index)
{
    if (index > v->count)
    {
        printf("VECTOR : ERROR, index %zu is out of bound", index);
        exit(-1);
    }
    if (index == v->count)
    {
        char *target_addr = (char *)v->data + (index + v->item_size);
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

void VectorPopByName(Vector *v, const char *name)
{
    //TODO
}

void *VectorGet(Vector *v, size_t index)
{
    return (void *)((char *)v->data + (index * v->item_size));
}

void *VectorGetByName(Vector *v, const char *name)
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
            return (void *)target_addr;
        }
    }
    return nullptr;
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
    printf("VECTOR : ERROR, cannot find index of name : %s", name);
    exit(-1);    
}

void VectorFree(Vector *v)
{
    v->item_size = 0;
    v->count = 0;
    v->capacity = 0;
    free(v->data);
}
