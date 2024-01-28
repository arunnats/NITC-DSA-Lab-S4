#include <stdio.h>
#include <stdlib.h>

// Helper functions

struct Node
{
    int key;
    struct Node *l;
    struct Node *r;
};

struct QueueNode
{
    struct Node *node;
    struct QueueNode *next;
};

struct Queue
{
    struct QueueNode *front;
    struct QueueNode *rear;
};

struct StackNode
{
    struct Node *node;
    struct StackNode *next;
};

struct Stack
{
    struct StackNode *top;
};

struct Stack *createStack()
{
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    s->top = NULL;
    return s;
}

void push(struct Stack *s, struct Node *node)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = s->top;
    s->top = newNode;
}

struct Node *pop(struct Stack *s)
{
    if (s->top == NULL)
        return NULL;

    struct StackNode *temp = s->top;
    struct Node *node = temp->node;

    s->top = temp->next;
    free(temp);

    return node;
}

int isEmpty(struct Stack *s)
{
    return (s->top == NULL);
}

struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Node *node, struct Queue *Q)
{
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (Q->rear == NULL)
    {
        Q->front = Q->rear = newNode;
    }
    else
    {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
}

struct Node *dequeue(struct Queue *Q)
{
    if (Q->front == NULL)
        return NULL;

    struct QueueNode *temp = Q->front;
    struct Node *node = temp->node;

    Q->front = temp->next;

    if (Q->front == NULL)
    {
        Q->rear = NULL;
    }

    free(temp);

    return node;
}

struct Node *initializeNode(int x)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = x;
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
}

int intMax(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int search(int arr[], int start, int end, int key)
{
    for (int i = start; i <= end; i++)
    {
        if (key == arr[i])
        {
            return i;
        }
    }
    return -1;
}

void printLevelOrder(struct Node *root) // for testing
{
    if (root == NULL)
        return;

    struct Queue Q;
    Q.front = Q.rear = NULL;

    enqueue(root, &Q);

    while (Q.front != NULL)
    {
        struct Node *currentNode = dequeue(&Q);
        printf("%d ", currentNode->key);

        if (currentNode->l != NULL)
            enqueue(currentNode->l, &Q);

        if (currentNode->r != NULL)
            enqueue(currentNode->r, &Q);

        free(currentNode);
    }
}
// End of Helper functions

struct Node *buildTree(int inorder[], int preorder[], int inStart, int inEnd, int *preIndex)
{
    if (inStart > inEnd)
        return NULL;

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = preorder[*preIndex];
    newNode->l = newNode->r = NULL;

    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++)
    {
        if (inorder[inIndex] == newNode->key)
            break;
    }

    (*preIndex)++;
    newNode->l = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    newNode->r = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);

    return newNode;
}

void printZigZagOrder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack *s1 = createStack();
    struct Stack *s2 = createStack();

    push(s1, root);

    while (!isEmpty(s1) || !isEmpty(s2))
    {
        while (!isEmpty(s1))
        {
            struct Node *temp = pop(s1);
            printf("%d ", temp->key);

            if (temp->l)
                push(s2, temp->l);
            if (temp->r)
                push(s2, temp->r);
        }

        while (!isEmpty(s2))
        {
            struct Node *temp = pop(s2);
            printf("%d ", temp->key);

            if (temp->r)
                push(s1, temp->r);
            if (temp->l)
                push(s1, temp->l);
        }
    }

    free(s1);
    free(s2);
}
