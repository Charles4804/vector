#include "vector/vector.h"
#include <stdio.h>

int main(int argc, const char *argv[])
{
    printf("%s : running tests\n", argv[0]);
    Vector *v = (Vector *)malloc(sizeof(Vector));
    char *st = "MATE";
    VectorNew(v, sizeof(char *));
    
    VectorPush(v, "hello");
    VectorPush(v, "World");

    printf("%zu\n", v->capacity);

    VectorPush(v, st);

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0: %s 1: %s 2: %s\n", (char *)VectorGet(v, 0), (char *)VectorGet(v, 1), (char *)VectorGet(v, 2));
    printf("%s, %s, %s\n", (char *)VectorGetByName(v, "hello"), (char *)VectorGetByName(v, "World"), (char *)VectorGetByName(v, "Mate"));
    VectorPop(v, 2);
    printf("%zu count\n", v->count);
    VectorPop(v, 0);
    printf("%zu cont\n", v->count);
    printf("0: %s\n", (char *)VectorGet(v, 0));
    VectorPush(v, "kjeh");
    printf("1: %s\n", (char *)VectorGet(v, 1));

    VectorFree(v);
    free(v);
    return 0;
}
