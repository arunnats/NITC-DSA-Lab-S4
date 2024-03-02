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

int hashFunction(int key, int maxSize)
{
    return key % maxSize;
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

int search(struct HashMap *map, int key, int maxSize)
{
    int index = hashFunction(key, maxSize);

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

void insertLinear(struct HashMap *map, int key, int maxSize)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->key = key;

    int index = hashFunction(key, maxSize);

    while (map->array[index] != NULL)
    {
        index = (index + 1) % SIZE;
    }

    map->array[index] = newNode;
}

void unionFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *red_map)
{
    //clearHashmap(map, maxSize);
	 
    struct HashMap *map = createHashmap(maxSize);
	    
    for (int i = 0; i < sizeA; i++)
    {
        if (!search(map, A[i], maxSize))
        {
            insertLinear(map, A[i], maxSize);
            printf("%d ", A[i]);
        }
    }

    for (int i = 0; i < sizeB; i++)
    {
        if (!search(map, B[i], maxSize))
        {
            insertLinear(map, B[i], maxSize);
            printf("%d ", B[i]);
        }
    }
    
    //clearHashmap(map, maxSize);
    free(map);
}

void intersectionFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *redundandt_map)
{
    //clearHashmap(map, maxSize);
    struct HashMap *map = createHashmap(maxSize);
    
    int count1;
    for (int i = 0; i < sizeB; i++)
    {
    	if (!search(map, B[i], maxSize))
        {
        	insertLinear(map, B[i], maxSize);
        	count1++;
        }
    }

    int count2 = count1;
    for (int i = 0; i < sizeA; i++)
    {
        if (search(map, A[i], maxSize))
        {
            printf("%d ", A[i]);
            map->array[hashFunction(A[i], maxSize)] = NULL;
            count1--;
        }
    }
    
    if(count1==count2)
    {
        printf("-1");
    }
        free(map);
}

void setDifferenceFunc(int *A, int *B, int sizeA, int sizeB, int maxSize, struct HashMap *red_map)
{

    //clearHashmap(map, maxSize);

   struct HashMap *map = createHashmap(maxSize);

    for (int i = 0; i < sizeB; i++)
    {
        if (!search(map, B[i], maxSize))
        {
        	insertLinear(map, B[i], maxSize);
        }
    }

    int isEmpty = 1;
    for (int i = 0; i < sizeA; i++)
    {
        if (!search(map, A[i], maxSize))
        {
            printf("%d ", A[i]);
            insertLinear(map, A[i], maxSize);
            isEmpty = 0;
        }
    }

    if (isEmpty)
    {
        printf("-1");
    }
        free(map);
}

int main()
{
    int sizeA, sizeB;
    scanf("%d %d", &sizeA, &sizeB);
    int A[sizeA];
    int B[sizeB];

    for (int i = 0; i < sizeA; i++)
    {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < sizeB; i++)
    {
        scanf("%d", &B[i]);
    }

    int maxSize = 2 * (sizeA + sizeB);

    struct HashMap *map = createHashmap(maxSize);

    char char1, char2;

    char option;
    do
    {
        scanf(" %c", &option);
        switch (option)
        {
        case 'u':
            scanf(" %c %c", &char1, &char2);
            if (char1 == 'A' && char2 == 'B')
            {
                unionFunc(A, B, sizeA, sizeB, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else if (char1 == 'B' && char2 == 'A')
            {
                unionFunc(B, A, sizeB, sizeA, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else
            {
                printf("-1");
            }
            printf("\n");
            break;

        case 'i':
            scanf(" %c %c", &char1, &char2);
            if (char1 == 'A' && char2 == 'B')
            {
                intersectionFunc(A, B, sizeA, sizeB, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else if (char1 == 'B' && char2 == 'A')
            {
                intersectionFunc(B, A, sizeB, sizeA, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else
            {
                printf("-1");
            }
            printf("\n");

            break;

        case 's':
            scanf(" %c %c", &char1, &char2);
            if (char1 == 'A' && char2 == 'B')
            {
                setDifferenceFunc(A, B, sizeA, sizeB, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else if (char1 == 'B' && char2 == 'A')
            {
                setDifferenceFunc(B, A, sizeB, sizeA, maxSize, map);
                clearHashmap(map, maxSize);
            }
            else
            {
                printf("-1");
            }
            printf("\n");
            break;

        case 'e':
            break;
        }

    } while (option != 'e');

    return 1;
}
