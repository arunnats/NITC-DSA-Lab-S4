#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int degree;
    int marked;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct FibonacciHeap
{
    Node *min;
    int size;
} FibonacciHeap;