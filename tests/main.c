#include "Vector/vector.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void Test() 
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    VectorNew(v, sizeof(int));

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    VectorPush(v, &(int){2});
    VectorPush(v, &(int){64242342});
    VectorPush(v, &(int){2342934});
    printf("%zu, %zu\n", v->count, v->capacity);
    printf("0: %d, 1 : %d, 2 : %d\n", *(int *)VectorGet(v, 0), *(int *)VectorGet(v, 1), *(int *)VectorGet(v, 2));
    printf("value :: 0 : %d 1 : %d 2 : %d\n",
         *(int *)VectorGetByValue(v, &(int){2}, 0),
         *(int *)VectorGetByValue(v, &(int){64242342}, 0),
         *(int *)VectorGetByValue(v, &(int){2342934}, 0));
    VectorPop(v, 0);
    VectorPop(v, 0);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0: %d\n", *(int *)VectorGet(v, 0));
    printf("value 132 exists : %d\n", VectorValueExists(v, &(int){132}, 0));
    printf("value 2342934 exists : %d\n",
         VectorValueExists(v, &(int){2342934}, 0));
    VectorReplace(v, 0, &(int){243});
    printf("0: %d\n", *(int *)VectorGet(v, 0));
    printf("error code : %d\n", VectorInsert(v, 0, &(int){67}));
    printf("%zu %zu\n", v->count, v->capacity);
    printf("0: %d 1: %d\n", *(int *)VectorGet(v, 0), *(int *)VectorGet(v, 1));
    printf("error code : %d\n", VectorInsert(v, 1, &(int){6767}));
    printf("0: %d, 1: %d 2: %d\n", *(int *)VectorGet(v, 0),
         *(int *)VectorGet(v, 1), *(int *)VectorGet(v, 2));

    VectorPopByValue(v, &(int){243}, 0);
    printf("0 : %d, 1 : %d\n", *(int *)VectorGet(v, 0), *(int*)VectorGet(v, 1));
    VectorFree(v);
    free(v);
}

void Test2() {
  Vector *v = (Vector *)malloc(sizeof(Vector));

  VectorNew(v, sizeof(int));

  printf("count : %zu capacity : %zu\n", v->count, v->capacity);
  VectorPush(v, &(int){2});
  VectorPush(v, &(int){64242342});
  VectorPush(v, &(int){2342934});
  VectorPush(v, &(int){12322});
  VectorPush(v, &(int){2312});
  printf("0 : %d 1 : %d 2 : %d 3 : %d 4 : %d\n", *(int *)VectorGet(v, 0),
         *(int *)VectorGet(v, 1), *(int *)VectorGet(v, 2),
         *(int *)VectorGet(v, 3), *(int *)VectorGet(v, 4));
  printf("count : %zu capacity : %zu\n", v->count, v->capacity);
  VectorPopRangeFast(v, 1, 3);
  printf("count : %zu capacity : %zu\n", v->count, v->capacity);
  printf("0 : %d 1:%d\n", *(int *)VectorGet(v, 0), *(int *)VectorGet(v, 1));
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
        VectorPush(v, &i);
    }

    clock_t start = clock();

    if (argc > 1)
    {
        VectorPop(v, 0);
    }
    else
    {
        VectorPopFast(v, 0);
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

    VectorPush(v, &apple);
    VectorPush(v, &banana);
    VectorPush(v, &mango);

    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0 : %s 1 : %s 2 : %s\n", *(char **)VectorGet(v, 0), *(char **)VectorGet(v, 1), *(char **)VectorGet(v, 2));
    printf("0 : %d 1 : %d 2 : %d\n", VectorValueExists(v, &(char*){"Apple"}, 1), VectorValueExists(v, &(char*){"Banana"}, 1), VectorValueExists(v, &(char*){"Mango"}, 1));
    
    VectorPopByValue(v, &(char *){"Banana"}, 1);
    printf("count : %zu capacity : %zu\n", v->count, v->capacity);
    printf("0 : %s 1 : %s\n", *(char **)VectorGet(v, 0), *(char **)VectorGet(v, 1));
    printf("apple : %zu mango : %zu\n", VectorGetIndexByValue(v, &(char*){"Apple"}, 1), VectorGetIndexByValue(v, &(char*){"Mango"}, 1));

    VectorFree(v);

    Test();
    Test2();
    return 0;
}
