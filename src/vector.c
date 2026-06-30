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
            exit(-1);
        }
        v->data = tmp;
    }
    char *target_addr = (char *)v->data + (v->count * v->item_size);
    memcpy(target_addr, item, v->item_size);
    v->count++;
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

void VectorFree(Vector *v)
{
    v->item_size = 0;
    v->count = 0;
    v->capacity = 0;
    free(v->data);
}
