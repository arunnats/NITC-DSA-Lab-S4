#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node
{
    int key;
    int color;
    struct Node *l;
    struct Node *r;
    struct Node *p;
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

struct Stack *createStack();
void push(struct Stack *s, struct Node *node);
struct Node *pop(struct Stack *s);
int isEmpty(struct Stack *s);

struct Queue *createQueue();
void enqueue(struct Node *node, struct Queue *Q);
struct Node *dequeue(struct Queue *Q);

struct Node *createNode(int key);

void leftRotate(struct Node *root, struct Node *x);
void rightRotate(struct Node *root, struct Node *y);

struct Node *findRoot(struct Node *node);

void insertFixup(struct Node *root, struct Node *node);
struct Node *insertRB(struct Node *root, int key);

void fixupCase1(struct Node *node);
void fixupCase2(struct Node *root, struct Node *node);
void fixupCase3(struct Node *root, struct Node *node);

void inorderTraversal(struct Node *root);
void printLevelOrder(struct Node *root);

struct Node *createNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->p = NULL;
    return newNode;
}

void leftRotate(struct Node *root, struct Node *x)
{
    struct Node *y = x->r;
    x->r = y->l;

    if (y->l != NULL)
        y->l->p = x;

    y->p = x->p;

    if (x->p == NULL)
        root = y;
    else if (x == x->p->l)
        x->p->l = y;
    else
        x->p->r = y;

    y->l = x;
    x->p = y;
}

void rightRotate(struct Node *root, struct Node *y)
{
    struct Node *x = y->l;
    y->l = x->r;

    if (x->r != NULL)
        x->r->p = y;

    x->p = y->p;

    if (y->p == NULL)
        root = x;
    else if (y == y->p->l)
        y->p->l = x;
    else
        y->p->r = x;

    x->r = y;
    y->p = x;
}

struct Node *findRoot(struct Node *node)
{
    while (node->p != NULL)
    {
        node = node->p;
    }
    return node;
}

void insertFixup(struct Node *root, struct Node *node)
{
    while (node->p != NULL && node->p->color == RED && node->p->p != NULL)
    {
        if (node->p == node->p->p->l)
        {
            struct Node *uncle = node->p->p->r;

            if (uncle != NULL && uncle->color == RED)
                fixupCase1(node);
            else
            {
                if (node == node->p->r)
                    fixupCase2(root, node);
                else
                    fixupCase3(root, node);
            }
        }
        else
        {
            struct Node *uncle = node->p->p->l;

            if (uncle != NULL && uncle->color == RED)
                fixupCase1(node);
            else
            {
                if (node == node->p->l)
                    fixupCase2(root, node);
                else
                    fixupCase3(root, node);
            }
        }
    }

    root->color = BLACK;
}

struct Node *insertRB(struct Node *root, int key)
{
    struct Node *node = createNode(key);

    if (root == NULL)
        return node;

    struct Node *parent = NULL;
    struct Node *current = root;

    while (current != NULL)
    {
        parent = current;
        if (key < current->key)
            current = current->l;
        else if (key > current->key)
            current = current->r;
        else
        {
            free(node);
            return root;
        }
    }

    node->p = parent;
    if (key < parent->key)
        parent->l = node;
    else
        parent->r = node;

    insertFixup(root, node);

    return findRoot(node);
}

void fixupCase1(struct Node *node)
{
    node->p->color = BLACK;
    node->p->p->color = RED;
    node = node->p->p;
}

void fixupCase2(struct Node *root, struct Node *node)
{
    node = node->p;
    leftRotate(root, node);
}

void fixupCase3(struct Node *root, struct Node *node)
{
    node->p->color = BLACK;
    node->p->p->color = RED;
    rightRotate(root, node->p->p);
}

void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->l);
        printf("%d ", root->key);
        inorderTraversal(root->r);
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

void printParenthesisRep(struct Node *node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }

    printf("(%d %c ", node->key, (node->color == RED) ? 'R' : 'B');
    printParenthesisRep(node->l);
    printParenthesisRep(node->r);
    printf(") ");
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
        case 'i':
            scanf(" %d", &x);
            root = insertRB(root, x);
            break;

        case 'p':
            inorderTraversal(root);
            printf("\n");
            break;

        case 'l':
            printLevelOrder(root);
            printf("\n");
            break;

        case 'b':
            printParenthesisRep(root);
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
