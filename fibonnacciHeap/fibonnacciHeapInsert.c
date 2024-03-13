#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    int degree;
    int marked;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
};

struct FibonacciHeap
{
    struct Node *min;
    int N;
};

struct FibonacciHeap *createFibonacciHeap()
{
    struct FibonacciHeap *fibHeap = (struct FibonacciHeap *)malloc(sizeof(struct FibonacciHeap));
    fibHeap->min = NULL;
    fibHeap->N = 0;
    return fibHeap;
}

struct Node *createNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->marked = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    return newNode;
}

struct FibonacciHeap *mergeWithRootList(struct FibonacciHeap *fibHeap, struct Node *newNode)
{
    if (fibHeap->min == NULL)
    {
        fibHeap->min = newNode;
    }
    else
    {
        newNode->left = fibHeap->min;
        newNode->right = fibHeap->min->right;
        fibHeap->min->right->left = newNode;
        fibHeap->min->right = newNode;
    }

    return fibHeap;
}

struct FibonacciHeap *insert(struct FibonacciHeap *fibHeap, int key)
{
    struct Node *newNode = createNode(key);

    fibHeap = mergeWithRootList(fibHeap, newNode);

    if (fibHeap->min == NULL || newNode->key < fibHeap->min->key)
    {
        fibHeap->min = newNode;
    }

    fibHeap->N++;
    return fibHeap;
}

struct FibonacciHeap *unionHeap(struct FibonacciHeap *fibHeap1, struct FibonacciHeap *fibHeap2)
{
    struct FibonacciHeap *newHeap = createFibonacciHeap();

    if (fibHeap1->min == NULL)
    {
        newHeap->min = fibHeap2->min;
    }
    else if (fibHeap2->min == NULL)
    {
        newHeap->min = fibHeap1->min;
    }
    else
    {
        newHeap->min->right = fibHeap1->min;
        fibHeap1->min->left = newHeap->min;
        fibHeap2->min->left->right = fibHeap1->min->right;
        fibHeap1->min->right->left = fibHeap2->min->left;
        fibHeap1->min->right = fibHeap2->min;
        fibHeap2->min->left = fibHeap1->min;

        if (fibHeap1->min->key < fibHeap2->min->key)
        {
            newHeap->min = fibHeap1->min;
        }
        else
        {
            newHeap->min = fibHeap2->min;
        }
    }

    newHeap->N = fibHeap1->N + fibHeap2->N;

    return newHeap;
}

void printRootList(struct Node *min)
{
    if (min == NULL)
    {
        printf("Empty heap\n");
        return;
    }

    struct Node *current = min;
    do
    {
        printf("%d ", current->key);
        current = current->right;
    } while (current != min);

    printf("\n");
}