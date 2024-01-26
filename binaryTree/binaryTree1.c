#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *l;
    struct Node *r;
};

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
        printf("%d", root->key);
        printInOrder(root->r);
    }
}

void printPostOrder(struct Node *root)
{
    if (root != NULL)
    {
        printPostOrder(root->l);
        printPostOrder(root->r);
        printf("%d", root->key);
    }
}

void printPreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d", root->key);
        printPreOrder(root->l);
        printPreOrder(root->r);
    }
}
