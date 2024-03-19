#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node
{
    int key;
    int degree;
    int mark;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
};

struct FibonacciHeap
{
    int n;
    struct Node *min;
    struct Node *root_list;
};

struct Node *createNode(int key);
struct FibonacciHeap *createFibonacciHeap();
struct Node *insert(struct FibonacciHeap *fibHeap, int key);
struct FibonacciHeap *unionHeap(struct FibonacciHeap *fibHeap1, struct FibonacciHeap *fibHeap2);
struct Node *extractMin(struct FibonacciHeap *fibHeap);
void consolidate(struct FibonacciHeap *fibHeap);
struct Node *mergeWithRootList(struct Node *rootList, struct Node *node);
void printFibonacciHeap(struct FibonacciHeap *fibHeap);

int main()
{
    struct FibonacciHeap *fibHeap = createFibonacciHeap();

    insert(fibHeap, 5);
    insert(fibHeap, 2);
    insert(fibHeap, 16);
    insert(fibHeap, 9);

    printf("After insertion:\n");
    printFibonacciHeap(fibHeap);

    struct Node *minNode = extractMin(fibHeap);
    if (minNode != NULL)
    {
        printf("Extracted minimum node with key: %d\n", minNode->key);
    }
    else
    {
        printf("Fibonacci heap is empty!\n");
    }

    printf("After extraction:\n");
    printFibonacciHeap(fibHeap);

    return 0;
}

struct Node *createNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->mark = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct FibonacciHeap *createFibonacciHeap()
{
    struct FibonacciHeap *fibHeap = (struct FibonacciHeap *)malloc(sizeof(struct FibonacciHeap));
    fibHeap->n = 0;
    fibHeap->min = NULL;
    fibHeap->root_list = NULL;
    return fibHeap;
}

struct Node *insert(struct FibonacciHeap *fibHeap, int key)
{
    struct Node *node = createNode(key);
    node->left = node;
    node->right = node;

    if (fibHeap->root_list == NULL)
    {
        fibHeap->root_list = node;
    }
    else
    {
        node->right = fibHeap->root_list;
        node->left = fibHeap->root_list->left;
        fibHeap->root_list->left->right = node;
        fibHeap->root_list->left = node;
    }

    if (fibHeap->min == NULL || node->key < fibHeap->min->key)
    {
        fibHeap->min = node;
    }

    fibHeap->n++;
    return node;
}

struct FibonacciHeap *unionHeap(struct FibonacciHeap *fibHeap1, struct FibonacciHeap *fibHeap2)
{
    struct FibonacciHeap *FH = createFibonacciHeap();
    FH->root_list = fibHeap1->root_list;

    FH->min = (fibHeap1->min->key < fibHeap2->min->key) ? fibHeap1->min : fibHeap2->min;

    fibHeap1->root_list->left->right = fibHeap2->root_list;
    fibHeap2->root_list->left->right = fibHeap1->root_list;
    struct Node *temp = fibHeap1->root_list->left;
    fibHeap1->root_list->left = fibHeap2->root_list->left;
    fibHeap2->root_list->left = temp;

    FH->n = fibHeap1->n + fibHeap2->n;

    return FH;
}

struct Node *extractMin(struct FibonacciHeap *fibHeap)
{
    struct Node *min = fibHeap->min;

    if (min != NULL)
    {
        if (min->child != NULL)
        {
            struct Node *child = min->child;
            do
            {
                struct Node *nextChild = child->right;
                fibHeap->root_list->left->right = child;
                child->left = fibHeap->root_list->left;
                child->right = fibHeap->root_list;
                fibHeap->root_list->left = child;
                child->parent = NULL;
                child = nextChild;
            } while (child != min->child);
        }

        if (min == min->right)
        {
            fibHeap->min = NULL;
            fibHeap->root_list = NULL;
        }
        else
        {
            min->left->right = min->right;
            min->right->left = min->left;
            fibHeap->min = min->right;
            consolidate(fibHeap);
        }

        fibHeap->n--;
    }

    return min;
}

void consolidate(struct FibonacciHeap *fibHeap)
{
    int maxDegree = (int)(log(fibHeap->n) * 2) + 1;
    struct Node *A[maxDegree];

    for (int i = 0; i < maxDegree; i++)
    {
        A[i] = NULL;
    }

    struct Node *current = fibHeap->root_list;
    do
    {
        struct Node *x = current;
        current = current->right;

        int d = x->degree;
        while (A[d] != NULL)
        {
            struct Node *y = A[d];
            if (x->key > y->key)
            {
                struct Node *temp = x;
                x = y;
                y = temp;
            }
            if (y == fibHeap->min)
            {
                fibHeap->min = x;
            }
            fibHeap->root_list->left->right = y->right;
            y->right->left = fibHeap->root_list->left;
            y->left->right = y->right;
            y->right->left = y->left;
            x->child = mergeWithRootList(x->child, y);
            y->parent = x;
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    } while (current != fibHeap->root_list);

    fibHeap->min = NULL;
    for (int i = 0; i < maxDegree; i++)
    {
        if (A[i] != NULL)
        {
            if (fibHeap->min == NULL || A[i]->key < fibHeap->min->key)
            {
                fibHeap->min = A[i];
            }
        }
    }
}

struct Node *mergeWithRootList(struct Node *rootList, struct Node *node)
{
    if (rootList == NULL)
    {
        return node;
    }

    node->right = rootList;
    node->left = rootList->left;
    rootList->left->right = node;
    rootList->left = node;

    return rootList;
}

void printFibonacciHeap(struct FibonacciHeap *fibHeap)
{
    printf("Total nodes: %d\n", fibHeap->n);
    printf("Minimum: %d\n", (fibHeap->min != NULL) ? fibHeap->min->key : -1);
    printf("Root list: ");
    struct Node *current = fibHeap->root_list;
    if (current != NULL)
    {
        do
        {
            printf("%d ", current->key);
            current = current->right;
        } while (current != fibHeap->root_list);
    }
    printf("\n");
}
