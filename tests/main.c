#include "Vector/vector.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void Test(Vector *vv) 
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    VectorNew(v, sizeof(int));

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    VectorAdd(v, &(int){2});
    VectorAdd(v, &(int){64242342});
    VectorAdd(v, &(int){2342934});
    printf("%zu, %zu\n", v->count, v->capacity);
    printf("0: %d, 1 : %d, 2 : %d\n", *(int *)VectorGetAt(v, 0), *(int *)VectorGetAt(v, 1), *(int *)VectorGetAt(v, 2));
    printf("value :: 0 : %d 1 : %d 2 : %d\n",
         *(int *)VectorGet(v, &(int){2}, 0),
         *(int *)VectorGet(v, &(int){64242342}, 0),
         *(int *)VectorGet(v, &(int){2342934}, 0));
    VectorRemoveAt(v, 0);
    VectorRemoveAt(v, 0);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0: %d\n", *(int *)VectorGetAt(v, 0));
    printf("value 132 exists : %d\n", VectorContains(v, &(int){132}, 0));
    printf("value 2342934 exists : %d\n",
         VectorContains(v, &(int){2342934}, 0));
    VectorReplace(v, 0, &(int){243});
    printf("0: %d\n", *(int *)VectorGetAt(v, 0));
    printf("error code : %d\n", VectorInsert(v, 0, &(int){67}));
    printf("%zu %zu\n", v->count, v->capacity);
    printf("0: %d 1: %d\n", *(int *)VectorGetAt(v, 0), *(int *)VectorGetAt(v, 1));
    printf("error code : %d\n", VectorInsert(v, 1, &(int){6767}));
    printf("0: %d, 1: %d 2: %d\n", *(int *)VectorGetAt(v, 0),
         *(int *)VectorGetAt(v, 1), *(int *)VectorGetAt(v, 2));

    VectorRemove(v, &(int){243}, 0);
    printf("0 : %d, 1 : %d\n", *(int *)VectorGetAt(v, 0), *(int*)VectorGetAt(v, 1));
    VectorFree(v);
    free(v);
}

void Test2()
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    VectorNew(v, sizeof(int));

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    VectorAdd(v, &(int){2});
    VectorAdd(v, &(int){64242342});
    VectorAdd(v, &(int){2342934});
    VectorAdd(v, &(int){12322});
    VectorAdd(v, &(int){2312});
    printf("0 : %d 1 : %d 2 : %d 3 : %d 4 : %d\n", *(int *)VectorGetAt(v, 0),
         *(int *)VectorGetAt(v, 1), *(int *)VectorGetAt(v, 2),
         *(int *)VectorGetAt(v, 3), *(int *)VectorGetAt(v, 4));
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    VectorRemoveRange(v, 1, 3);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0 : %d 1:%d\n", *(int *)VectorGetAt(v, 0), *(int *)VectorGetAt(v, 1));
    Vector *vv = (Vector *)malloc(sizeof(Vector));
    VectorNew(vv, sizeof(int));
    
    VectorAdd(vv, &(int){33});
    VectorAdd(vv, &(int){1463});
    VectorAdd(vv, &(int){729463});
    VectorAdd(vv, &(int){6723});
    VectorAdd(vv, &(int){673});
    VectorAdd(vv, &(int){3});
    
    printf("%zu %zu\n", v->capacity, v->count);
    VectorAddRange(v, vv);
    
    for (int i = 0; i < v->count; i++)
    {
        printf("%d\n", *(int *)VectorGetAt(v, i));
    }
    printf("%zu %zu\n", v->capacity, v->count);
    VectorFree(vv);
    VectorFree(v);
    free(v);
}

int main(int argc, const char *argv[]) 
{
    /*
    Vector *v = (Vector *)malloc(sizeof(Vector));
    VectorNew(v, 4);
    for (int i = 0; i < 100000000; i++)
    {
        VectorAdd(v, &i);
    }

    clock_t start = clock();

    if (argc > 1)
    {
        VectorRemoveAt(v, 0);
    }
    else
    {
        VectorRemoveAtFast(v, 0);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Pop execution time: %f seconds\n", time_taken);
    
    VectorFree(v);
    */
    Vector *v = (Vector *)malloc(sizeof(Vector));
    VectorNew(v, sizeof(char *));
    
    char *apple = "Apple";
    char *banana = "Banana";
    char *mango = "Mango";
        
    VectorEnsureCapacity(v, 8);

    VectorAdd(v, &apple);
    VectorAdd(v, &banana);
    VectorAdd(v, &mango);

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0 : %s 1 : %s 2 : %s\n", *(char **)VectorGetAt(v, 0), *(char **)VectorGetAt(v, 1), *(char **)VectorGetAt(v, 2));
    printf("0 : %d 1 : %d 2 : %d\n", VectorContains(v, (char*){"Apple"}, 1), VectorContains(v, (char*){"Banana"}, 1), VectorContains(v, (char*){"Mango"}, 1));
    
    VectorRemove(v, (char *){"Banana"}, 1);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0 : %s 1 : %s\n", *(char **)VectorGetAt(v, 0), *(char **)VectorGetAt(v, 1));
    printf("apple : %zu mango : %zu\n", VectorGetIndex(v, (char*){"Apple"}, 1), VectorGetIndex(v, (char*){"Mango"}, 1));
    //char **fruits = (char **)VectorGetArray(v);
    char **fruits = malloc(32);
    VectorCopyTo(v, 0, fruits);
    printf("%s %s\n", fruits[0], fruits[1]);


    Test(v);
    VectorFree(v);
    Test2();
    return 0;
}
