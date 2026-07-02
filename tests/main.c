#include "vector/vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    VectorNew(v, sizeof(int));
    
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    VectorPush(v, &(int){2});
    VectorPush(v, &(int){64242342});
    VectorPush(v, &(int){2342934});
    printf("%zu, %zu\n", v->count, v->capacity);
    printf("0: %d, 1 : %d, 2 : %d\n", *(int *)VectorGet(v, 0), *(int *)VectorGet(v, 1), *(int *)VectorGet(v, 2));
    VectorPop(v, 0);
    VectorPop(v, 0);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0: %d\n", *(int *)VectorGet(v, 0));

    VectorFree(v);
    free(v);
    return 0;
}
