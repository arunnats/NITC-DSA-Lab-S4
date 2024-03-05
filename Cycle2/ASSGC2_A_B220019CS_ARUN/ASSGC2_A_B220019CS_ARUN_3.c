#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node
{
    int key;
    int colour;
    struct Node *l;
    struct Node *r;
    struct Node *p;
};

void leftRotate(struct Node *root, struct Node *x);
void rightRotate(struct Node *root, struct Node *y);

struct Node *findRoot(struct Node *node);

void insertFixup(struct Node *root, struct Node *node);
struct Node *insertRB(struct Node *root, int key);

void fixupCase1(struct Node *node);
void fixupCase2(struct Node *root, struct Node *node);
void fixupCase3(struct Node *root, struct Node *node);

struct Node *createNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->colour = RED;
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
    while (node->p != NULL && node->p->colour == RED && node->p->p != NULL)
    {
        if (node->p == node->p->p->l)
        {
            struct Node *uncle = node->p->p->r;

            if (uncle != NULL && uncle->colour == RED)
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

            if (uncle != NULL && uncle->colour == RED)
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

    root->colour = BLACK;
}

struct Node *insertRB(struct Node *root, int key)
{
    struct Node *node = createNode(key);

    if (root == NULL)
    {
        node->colour = BLACK;
        return node;
    }

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
    node->p->colour = BLACK;
    node->p->p->colour = RED;
    node = node->p->p;
}

void fixupCase2(struct Node *root, struct Node *node)
{
    node = node->p;
    leftRotate(root, node);
}

void fixupCase3(struct Node *root, struct Node *node)
{
    node->p->colour = BLACK;
    node->p->p->colour = RED;
    rightRotate(root, node->p->p);
}

void printParenthesisRep(struct Node *node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }

    printf("(%d %c ", node->key, (node->colour == RED) ? 'R' : 'B');
    printParenthesisRep(node->l);
    printParenthesisRep(node->r);
    printf(") ");
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
        root = insertRB(root, x);
        printParenthesisRep(root);
        printf("\n");
    }
    return 0;

    return 0;
}
