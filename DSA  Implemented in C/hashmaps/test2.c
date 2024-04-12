#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Node
{
    int key;
    struct Node *next;
};

struct HashMap
{
    struct Node *array[SIZE];
};

struct HashMap *createHashMap(int N)
{
    struct HashMap *map = (struct HashMap *)malloc(sizeof(struct HashMap));
    for (int i = 0; i < N; i++)
    {
        map->array[i] = NULL;
    }
    return map;
}

int hashFunction(int key, int N)
{
    return key % N;
}

void insert(struct HashMap *map, int key, int N)
{
    int index = hashFunction(key, N);

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = map->array[index];
    map->array[index] = newNode;
}

int search(struct HashMap *map, int key, int N)
{
    int index = hashFunction(key, N);
    struct Node *current = map->array[index];

    while (current != NULL)
    {
        if (current->key == key)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void countDistinct(struct HashMap *map, int arr[], int n, int k)
{
    for (int i = 0; i <= n - k; i++)
    {
        int distinctCount = 0;
        struct HashMap *windowMap = createHashMap(k);

        for (int j = 0; j < k; j++)
        {
            if (!search(windowMap, arr[i + j], k))
            {
                insert(windowMap, arr[i + j], k);
                distinctCount++;
            }
        }

        printf("%d ", distinctCount);

        free(windowMap);
    }
}

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    struct HashMap *map = createHashMap(N);

    // Insert the first K elements into the hashmap
    for (int i = 0; i < K; i++)
    {
        insert(map, arr[i], N);
    }

    // Call function to count distinct integers in each window of size K
    countDistinct(map, arr, N, K);

    free(map);

    return 0;
}
