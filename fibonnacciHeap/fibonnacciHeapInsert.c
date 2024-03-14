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

struct FibonacciHeap *removeFromRootList(struct FibonacciHeap *fibHeap, struct Node *min)
{
    if (min->right == min)
    {
        fibHeap->min = NULL;
    }
    else
    {
        min->left->right = min->right;
        min->right->left = min->left;
        fibHeap->min = min->right;
    }

    min->left = min->right = min;
    return fibHeap;
}

struct FibonacciHeap *mergeChildrenWithRootList(struct FibonacciHeap *fibHeap, struct Node *min)
{
    if (min->child != NULL)
    {
        struct Node *child = min->child;
        do
        {
            struct Node *nextChild = child->right;
            fibHeap = mergeWithRootList(fibHeap, child);
            child->parent = NULL;
            child = nextChild;
        } while (child != min->child);
    }
    return fibHeap;
}

struct FibonacciHeap *consolidate(struct FibonacciHeap *fibHeap)
{
    int maxDegree = (int)(log(fibHeap->N) * 2) + 1;
    struct Node *A[maxDegree];
    for (int i = 0; i < maxDegree; i++)
    {
        A[i] = NULL;
    }

    struct Node *current = fibHeap->min;
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
            heap_link(x, y);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    } while (current != fibHeap->min);

    fibHeap->min = NULL;
    for (int i = 0; i < maxDegree; i++)
    {
        if (A[i] != NULL)
        {
            if (fibHeap->min == NULL)
            {
                fibHeap->min = A[i];
                A[i]->left = A[i]->right = A[i];
            }
            else
            {
                A[i]->left = fibHeap->min;
                A[i]->right = fibHeap->min->right;
                fibHeap->min->right->left = A[i];
                fibHeap->min->right = A[i];
                if (A[i]->key < fibHeap->min->key)
                {
                    fibHeap->min = A[i];
                }
            }
        }
    }

    return fibHeap;
}

struct Node *extractMin(struct FibonacciHeap *fibHeap)
{
    struct Node *min = fibHeap->min;

    if (min != NULL)
    {
        fibHeap = removeFromRootList(fibHeap, min);
        fibHeap = mergeChildrenWithRootList(fibHeap, min);
        fibHeap = consolidate(fibHeap);

        return min;
    }
}

int main()
{
    char choice;
    int key;

    do
    {
        scanf(" %c", &choice);

        if (choice == 'i')
        {
        }
        else if (choice == 'm')
        {
        }
        else if (choice == 'e')
        {
        }
        else if (choice == 'p')
        {
        }
        else if (choice == 't')
        {
            break;
        }
    } while (1);

    return 0;
}
