#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
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
        map->array[i] == NULL;
    }
    return map;
}

void insertLinear(struct HashMap *map, int key, char value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;

    int index = hashFunction(key);

    while (map->array[index] != NULL && map->array[index]->key != key)
    {
        index = (index + 1) % SIZE;
    }

    map->array[index] = newNode;
}

void unionFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *map)
{
    for (int i = 0; i < sizeA; i++)
    {
        insertLinear(&map, A[i], 'A');
        printf("%d ", A[i]);
    }
}

void intersectionFunc(int *A, int *B, int maxSize, struct HashMap *map)
{
}

void setDifferenceFunc(int *A, int *B, int maxSize, struct HashMap *map)
{
}

int main()
{
    int sizeA, sizeB;
    scanf("%d %d", &sizeA, &sizeB);
    int A[sizeA];
    int B[sizeB];
    int maxSize = sizeA + sizeB;
    // if (sizeA > sizeB)
    //     maxSize = 2 * sizeA;
    // else
    //     maxSize = 2 * sizeB;

    struct HashMap *map = createHashmap(maxSize);

    char option;
    do
    {
        scanf(" %c", &option);
        switch (option)
        {

        case 'u':
            unionFunc(A, B, maxSize, &map);
            printf("\n");
            map = clearHashmap(&map, maxSize);

        case 'i':
            intersectionFunc(A, B, maxSize, &map);
            printf("\n");
            map = clearHashmap(&map, maxSize);

        case 's':
            setDifferenceFunc(A, B, maxSize, &map);
            printf("\n");
            map = clearHashmap(&map, maxSize);

        case 'e':
            break;

        default:
        }

    } while (option != 'e');

    free(map);

    return 1;
}