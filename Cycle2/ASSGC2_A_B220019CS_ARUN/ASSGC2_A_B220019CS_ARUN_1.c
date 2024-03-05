#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    int height;
    struct Node *l;
    struct Node *r;
};

struct Node *initializeNode(int x)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = x;
    newNode->height = 0;
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
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

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(struct Node *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

int getBalance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->l) - height(node->r);
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

struct Node *insertAVL(struct Node *root, int key)
{
    if (root == NULL)
        return initializeNode(key);

    if (key < root->key)
        root->l = insertAVL(root->l, key);
    else if (key > root->key)
        root->r = insertAVL(root->r, key);
    else
        return root;

    root->height = 1 + max(height(root->l), height(root->r));

    int balance = getBalance(root);

    if (balance > 1 && key < root->l->key)
        return rightRotate(root);

    if (balance < -1 && key > root->r->key)
        return leftRotate(root);

    if (balance > 1 && key > root->l->key)
    {
        root->l = leftRotate(root->l);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->r->key)
    {
        root->r = rightRotate(root->r);
        return leftRotate(root);
    }

    return root;
}

void printAncestors(struct Node *root, int key)
{
    if (root == NULL)
        return;

    if (key < root->key)
    {
        printf("%d ", root->key);
        printAncestors(root->l, key);
    }
    else if (key > root->key)
    {
        printf("%d ", root->key);
        printAncestors(root->r, key);
    }
    else
    {
        printf("%d ", root->key);
    }
}

void search(struct Node *root, int key, struct Node *ogRoot)
{
    if (root == NULL)
    {
        printf("-1\n");
        return;
    }

    if (key < root->key)
        search(root->l, key, ogRoot);
    else if (key > root->key)
        search(root->r, key, ogRoot);
    else
    {
        printAncestors(ogRoot, key);
        printf("\n");
    }
}

void calculateRotations(struct Node *node, int *leftRotations, int *rightRotations)
{
    if (node == NULL)
        return;

    int leftSubtree = 0, rightSubtree = 0;
    calculateRotations(node->l, &leftSubtree, &rightSubtree);

    *leftRotations = leftSubtree + (node->height < 0 ? 1 : 0) + rightSubtree;
    *rightRotations = rightSubtree + (node->height > 0 ? 1 : 0) + leftSubtree;
}

void calculate(struct Node *root)
{
    int leftRotations = 0, rightRotations = 0;
    calculateRotations(root, &leftRotations, &rightRotations);
    printf("%d %d", rightRotations, leftRotations);
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
            root = insertAVL(root, x);
            break;

        case 'p':
            printPreOrder(root);
            printf("\n");
            break;

        case 's':
            calculate(root);
            printf("\n");
            break;

        case 'x':
            scanf(" %d", &x);
            search(root, x, root);
            break;

        case 'e':
            break;

        default:
            break;
        }

    } while (choice != 'e');

    return 0;
}
