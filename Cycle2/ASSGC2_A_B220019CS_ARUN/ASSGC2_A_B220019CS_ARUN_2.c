#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    int value;
    int height;
    struct Node *l;
    struct Node *r;
};

struct Node *createNode(int key, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->height = 1;
    return newNode;
}

int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->l;
    struct Node *T2 = x->r;

    x->r = y;
    y->l = T2;

    y->height = max(height(y->l), height(y->r)) + 1;
    x->height = max(height(x->l), height(x->r)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->r;
    struct Node *T2 = y->l;

    y->l = x;
    x->r = T2;

    x->height = max(height(x->l), height(x->r)) + 1;
    y->height = max(height(y->l), height(y->r)) + 1;

    return y;
}

int getBalance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->l) - height(node->r);
}

struct Node *insert(struct Node *node, int key, int value)
{
    if (node == NULL)
        return createNode(key, value);

    if (key < node->key)
        node->l = insert(node->l, key, value);
    else if (key > node->key)
        node->r = insert(node->r, key, value);
    else
    {
        node->value = value;
        return node;
    }

    node->height = 1 + max(height(node->l), height(node->r));

    int balance = getBalance(node);

    if (balance > 1 && key < node->l->key)
        return rightRotate(node);

    if (balance < -1 && key > node->r->key)
        return leftRotate(node);

    if (balance > 1 && key > node->l->key)
    {
        node->l = leftRotate(node->l);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->r->key)
    {
        node->r = rightRotate(node->r);
        return leftRotate(node);
    }

    return node;
}

struct Node *lowerBound(struct Node *node, int key)
{
    if (node == NULL)
        return NULL;

    if (key <= node->key)
    {
        struct Node *leftLB = lowerBound(node->l, key);

        return (leftLB != NULL) ? leftLB : node;
    }

    return lowerBound(node->r, key);
}

struct Node *find(struct Node *node, int key)
{
    if (node == NULL)
        return NULL;

    if (key == node->key)
        return node;

    if (key < node->key)
        return find(node->l, key);
    else
        return find(node->r, key);
}

int size(struct Node *node)
{
    if (node == NULL)
        return 0;

    return 1 + size(node->l) + size(node->r);
}

int empty(struct Node *root)
{
    return (root == NULL) ? 1 : 0;
}

void printElements(struct Node *node)
{
    if (node == NULL)
        return;

    printElements(node->l);
    printf("%d ", node->key);
    printElements(node->r);
}

int main()
{
    struct Node *root = NULL;

    char choice;
    int key, value;

    do
    {
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'i':
            scanf("%d %d", &key, &value);
            root = insert(root, key, value);
            break;

        case 'l':
            scanf("%d", &key);
            struct Node *lbResult = lowerBound(root, key);
            if (lbResult != NULL)
                printf("%d %d\n", lbResult->key, lbResult->value);
            else
                printf("-1\n");
            break;

        case 'f':
            scanf("%d", &key);
            struct Node *findResult = find(root, key);
            if (findResult != NULL)
                printf("%d %d\n", findResult->key, findResult->value);
            else
                printf("-1\n");
            break;

        case 's':
            printf("%d\n", size(root));
            break;

        case 'e':
            printf("%d\n", empty(root));
            break;

        case 'p':
            printElements(root);
            printf("\n");
            break;

        case 't':
            break;

        default:
            break;
        }

    } while (choice != 't');

    return 1;
}