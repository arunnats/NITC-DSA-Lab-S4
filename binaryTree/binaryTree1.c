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

        case 't':
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 't');

    return 0;
}
