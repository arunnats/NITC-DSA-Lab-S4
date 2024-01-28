#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// End of Helper functions

void printLevelOrder(struct Node *root)
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
    }
}

void rightView(struct Node *root, int level, int *maxlevel)
{
    if (root == NULL)
        return;
    if (level > *maxlevel)
    {
        printf("%d ", root->key);
        *maxlevel = level;
    }

    rightView(root->r, level + 1, maxlevel);
    rightView(root->l, level + 1, maxlevel);
}

struct Node *buildTree(char *expression, int start, int end)
{
    if (start > end)
        return NULL;

    int num = 0;
    while (start <= end && expression[start] >= '0' && expression[start] <= '9')
    {
        num *= 10;
        num += (expression[start] - '0');
        start++;
    }

    struct Node *root = initializeNode(num);
    int count = 0;
    int index = -1;

    for (int i = start; i <= end; i++)
    {
        if (expression[i] == '(')
            count++;
        else if (expression[i] == ')')
            count--;

        if (count == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        root->l = buildTree(expression, start + 1, index - 1);
        root->r = buildTree(expression, index + 2, end - 1);
    }

    return root;
}

int main()
{
    char expression[1001];
    fgets(expression, sizeof(expression), stdin);
    size_t len = strlen(expression);

    if (len > 0 && expression[len - 1] == '\n')
    {
        expression[len - 1] = '\0';
        len--;
    }

    struct Node *root = buildTree(expression, 0, len - 1);
    return 1;
}