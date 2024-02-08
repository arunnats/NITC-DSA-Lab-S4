#include <stdio.h>
#include <stdlib.h>

#define SIZE 200
#define EMPTY -1

struct Node
{
    int key;
    char value;
};

struct HashMap
{
    struct Node *array[SIZE];
};

int hashFunction(int key)
{
    return key % SIZE;
}

struct HashMap *createHashmap(int maxSize)
{
    struct HashMap *map = (struct HashMap *)malloc(sizeof(struct HashMap));
    for (int i = 0; i < maxSize; i++)
    {
        map->array[i] = NULL;
    }
    return map;
}

struct HashMap *clearHashmap(struct HashMap *map, int maxSize)
{
    for (int i = 0; i < maxSize; i++)
    {
        map->array[i] = NULL;
    }
    return map;
}

void insertLinear(struct HashMap *map, int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->key = key;

    int index = hashFunction(key);

    while (map->array[index] != NULL)
    {
        index = (index + 1) % SIZE;
    }

    map->array[index] = newNode;
}

int search(struct HashMap *map, int key)
{
    int index = hashFunction(key);

    while (map->array[index] != NULL)
    {
        if (map->array[index]->key == key)
        {
            return 1;
        }
        index = (index + 1) % SIZE;
    }

    return 0;
}

void unionFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *map)
{
    for (int i = 0; i < sizeA; i++)
    {
        insertLinear(map, A[i]);
        printf("%d ", A[i]);
    }

    for (int i = 0; i < sizeB; i++)
    {
        if (!search(map, B[i]))
        {
            insertLinear(map, B[i]);
            printf("%d ", B[i]);
        }
    }
}

void intersectionFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *map)
{
    clearHashmap(map, maxSize);

    for (int i = 0; i < sizeB; i++)
    {
        insertLinear(map, B[i]);
    }

    for (int i = 0; i < sizeA; i++)
    {
        if (search(map, A[i]))
        {
            printf("%d ", A[i]);
        }
    }
}

void setDifferenceFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *map)
{
    // Insert elements from array A into the hashmap
    for (int i = 0; i < sizeA; i++)
    {
        insertLinear(map, A[i]);
        printf("%d ", A[i]);
    }

    // Clear the hashmap before processing array B
    // Process elements from array B and print the set difference
    for (int i = 0; i < sizeB; i++)
    {
        if (!search(map, B[i]))
        {
            printf("%d ", B[i]);
        }
    }
}

int main()
{
    int sizeA, sizeB;
    scanf("%d %d", &sizeA, &sizeB);
    int A[sizeA];
    int B[sizeB];
    int maxSize = 2 * (sizeA + sizeB);

    for (int i = 0; i < sizeA; i++)
    {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < sizeB; i++)
    {
        scanf("%d", &B[i]);
    }

    struct HashMap *map = createHashmap(maxSize);

    char option;
    do
    {
        scanf(" %c", &option);
        switch (option)
        {
        case 'u':
            unionFunc(A, B, sizeA, sizeB, maxSize, map);
            printf("\n");
            clearHashmap(map, maxSize);
            break;

        case 'i':
            intersectionFunc(A, B, sizeA, sizeB, maxSize, map);
            printf("\n");
            clearHashmap(map, maxSize);
            break;

        case 's':
            setDifferenceFunc(A, B, sizeA, sizeB, maxSize, map);
            printf("\n");
            clearHashmap(map, maxSize);
            break;

        case 'e':
            break;
        }

    } while (option != 'e');

    free(map);

    return 1;
}
