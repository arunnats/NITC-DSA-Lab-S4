#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void printRootListWithDeg(struct Node *min)
{
    if (min == NULL)
    {
        printf("Empty heap\n");
        return;
    }

    struct Node *current = min;
    do
    {
        printf("%d (%d)", current->key, current->degree);
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

void heap_link(struct Node *y, struct Node *x)
{
    if (y->right != y)
    {
        y->left->right = y->right;
        y->right->left = y->left;
    }
    else
    {
        x->child = NULL;
    }

    y->parent = x;
    if (x->child == NULL)
    {
        x->child = y;
        y->left = y->right = y;
    }
    else
    {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;

    y->marked = 0;
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

struct Node *findMin(struct Node *min)
{
    if (min == NULL)
    {
        return NULL;
    }

    struct Node *current = min;
    struct Node *minNode = min;
    do
    {
        if (current->key < minNode->key)
        {
            minNode = current;
        }
        current = current->right;
    } while (current != min);

    return minNode;
}

struct Node *extractMin(struct FibonacciHeap *fibHeap)
{
    struct Node *min = fibHeap->min;

    if (min != NULL)
    {
        fibHeap = removeFromRootList(fibHeap, min);
        fibHeap = mergeChildrenWithRootList(fibHeap, min);
        fibHeap = consolidate(fibHeap);

        fibHeap->min = findMin(fibHeap->min);

        return min;
    }

    return NULL;
}

int main()
{
    char choice;
    int key;
    struct FibonacciHeap *fibHeap = createFibonacciHeap();

    do
    {
        scanf(" %c", &choice);

        if (choice == 'i')
        {
            scanf("%d", &key);
            fibHeap = insert(fibHeap, key);
        }
        else if (choice == 'p')
        {
            printRootList(fibHeap->min);
        }
        else if (choice == 'd')
        {
            printRootListWithDeg(fibHeap->min);
        }
        else if (choice == 'e')
        {
            struct Node *min = extractMin(fibHeap);
            if (min != NULL)
            {
                printf("Minimum key : %d\n", min->key);
                free(min);
            }
            else
            {
                printf("The heap is empty.\n");
            }
        }
        else if (choice == 't')
        {
            break;
        }
        else
        {
        }
    } while (1);

    return 0;
}
