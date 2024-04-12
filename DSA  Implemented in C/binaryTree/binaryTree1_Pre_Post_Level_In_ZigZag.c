#include <stdio.h>
#include <stdlib.h>

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

void printInOrder(struct Node *root)
{
    if (root != NULL)
    {
        printInOrder(root->l);
        printf("%d ", root->key);
        printInOrder(root->r);
    }
}

void printPostOrder(struct Node *root)
{
    if (root != NULL)
    {
        printPostOrder(root->l);
        printPostOrder(root->r);
        printf("%d ", root->key);
    }
}

void printPreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        printPreOrder(root->l);
        printPreOrder(root->r);
    }
}

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

// void printZigZagOrder(struct Node *root)
// {
//     if (root == NULL)
//         return;

//     struct Queue *q = createQueue();
//     struct Stack *s = createStack();
//     int level = 0;

//     enqueue(root, q);

//     while (q->front != NULL)
//     {
//         int size = q->rear - q->front + 1;
//         for (int i = 0; i < size; i++)
//         {
//             struct Node *currentNode = dequeue(q);

//             if (level % 2 == 0)
//             {
//                 printf("%d ", currentNode->key);
//             }
//             else
//             {
//                 push(s, currentNode);
//             }

//             if (currentNode->l)
//                 enqueue(currentNode->l, q);
//             if (currentNode->r)
//                 enqueue(currentNode->r, q);
//         }

//         while (s->top != NULL)
//         {
//             struct Node *reversedNode = pop(s);
//             printf("%d ", reversedNode->key);
//         }
//         level++;
//     }
//     free(q);
//     free(s);
// }

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

struct Node *insertNode(struct Node *root, int key)
{
    if (root == NULL)
    {
        root = initializeNode(key);
        return root;
    }

    if (key < root->key)
    {
        root->l = insertNode(root->l, key);
    }
    else if (key > root->key)
    {
        root->r = insertNode(root->r, key);
    }

    return root;
}

int main()
{
    struct Node *root = NULL;

    char choice;
    int x;

    do
    {
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'a':
            scanf(" %d", &x);
            root = insertNode(root, x);
            break;

        case 'p':
            printPostOrder(root);
            printf("\n");
            break;

        case 'r':
            printPreOrder(root);
            printf("\n");
            break;

        case 'i':
            printInOrder(root);
            printf("\n");
            break;

        case 'l':
            printLevelOrder(root);
            printf("\n");
            break;

        case 'z':
            printZigZagOrder(root);
            printf("\n");
            break;

        case 't':
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 't');

    return 0;
}
