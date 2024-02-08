#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *next;
};

typedef struct Node Node;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

int findPrime(int n)
{
    int max = 0;
    int count = 0;

    for (int i = 2; i < n; i++)
    {
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
                count++;
            if (count > 1)
                break;
        }
        if (count == 0 && i > max)
            max = i;
        count = 0;
    }

    return max;
}

void insertLinear(Node **hashTable, int key, int *count, int n)
{
    int index = key % n;
    Node *newNode = createNode(key);

    int temp = 0;

    while (hashTable[(index + temp) % n] != NULL)
    {
        (*count)++;
        temp++;
    }

    hashTable[(index + temp) % n] = newNode;
    printf("%d ", (index + temp) % n);
}
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];

    Node *hashTable[n];

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        hashTable[i] = NULL;
    }

    int num;
    char waste;
    int i = 0;

    while (1)
    {
        scanf("%d", &num);
        arr[i++] = num;
        scanf("%c", &waste);
        if (waste == '\n')
            break;
    }

    for (int k = 0; k < i; k++)
    {
        insertLinear(hashTable, arr[k], &count, n);
    }

    printf("\n%d\n", count);

    count = 0;
    for (int i = 0; i < n; i++)
    {
        hashTable[i] = NULL;
    }

    for (int k = 0; k < i; k++)
    {
        insertQuad(hashTable, arr[k], &count, n);
    }

    printf("\n%d\n", count);

    count = 0;
    for (int i = 0; i < n; i++)
    {
        hashTable[i] = NULL;
    }

    for (int k = 0; k < i; k++)
    {
        insertDouble(hashTable, arr[k], &count, n);
    }
    printf("\n%d", count);

    return 0;
}
