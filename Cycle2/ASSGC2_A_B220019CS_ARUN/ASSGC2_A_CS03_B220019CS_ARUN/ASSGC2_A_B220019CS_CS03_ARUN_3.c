#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    int colour;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *createNode(int key, int colour, struct Node *parent)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->colour = colour;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

void leftRotate(struct Node **root, struct Node *x)
{
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node **root, struct Node *y)
{
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void fixCase1(struct Node **root, struct Node *node)
{
    node->parent->colour = 1;
    node->parent->parent->colour = 0;
    node = node->parent->parent;
}

void fixCase2(struct Node **root, struct Node *node)
{
    node = node->parent;
    leftRotate(root, node);
}

void fixCase3(struct Node **root, struct Node *node)
{
    node->parent->colour = 1;
    node->parent->parent->colour = 0;
    rightRotate(root, node->parent->parent);
}

void fix(struct Node **root, struct Node *z)
{
    while (z != *root && z->parent->colour == 0)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct Node *x = z->parent->parent->right;
            if (x != NULL && x->colour == 0)
                fixCase1(root, z);
            else
            {
                if (z == z->parent->right)
                    fixCase2(root, z);
                else
                    fixCase3(root, z);
            }
        }
        else
        {
            struct Node *x = z->parent->parent->left;
            if (x != NULL && x->colour == 0)
                fixCase1(root, z);
            else
            {
                if (z == z->parent->left)
                    fixCase2(root, z);
                else
                    fixCase3(root, z);
            }
        }
    }
    (*root)->colour = 1;
}

void insert(struct Node **root, int num)
{
    struct Node *z = createNode(num, 0, NULL);
    struct Node *x = *root;
    struct Node *y = NULL;
    while (x != NULL)
    {
        y = x;
        if (x->key > z->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
    {
        *root = z;
    }
    else
    {
        if (y->key > z->key)
            y->left = z;
        else
            y->right = z;
    }
    fix(root, z);
}

void printParenthesisRep(struct Node *node)
{
    if (node == NULL)
    {
        printf("()");
        return;
    }

    printf("(%d%c", node->key, (node->colour == 0) ? 'R' : 'B');
    printParenthesisRep(node->left);
    printParenthesisRep(node->right);
    printf(")");
}

int main()
{
    struct Node *root = NULL;

    char ch[5];

    while (fgets(ch, 5, stdin) && ch[0] != 'e')
    {
        int x = 0;
        int i = 0;
        while (ch[i] >= '0' && ch[i] <= '9')
        {
            x = x * 10 + (int)(ch[i] - '0');
            i++;
        }
        insert(&root, x);
        printParenthesisRep(root);
        printf("\n");
    }

    return 1;
}
