#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// constructing a red-black tree
// insert

struct node
{
    int key;
    char color;
    struct node *left;
    struct node *right;
    struct node *parent;
};

typedef struct node node;

node *createNode(int key)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->key = key;
    nn->color = 'R';
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    return nn;
}

char col(node *root)
{
    if (root == NULL)
        return 'B';
    return root->color;
}

node *leftRotate(node *z)
{
    node *y = z->right;
    z->right = y->left;

    if (y->left != NULL)
    {
        z->right->parent = z;
    }
    y->left = z;
    y->parent = z->parent;
    z->parent = y;
    // handle the parents
    return y;
}

node *rightRotate(node *z)
{
    node *y = z->left;
    z->left = y->right;

    if (y->right != NULL)
    {
        z->left->parent = z;
    }
    y->right = z;
    y->parent = z->parent;
    z->parent = y;
    return y;
}
// first insert the tree into the bst normally

node *insert(node *root, int key)
{
    if (root == NULL)
        root = createNode(key);
    else if (key < root->key)
    {
        root->left = insert(root->left, key);
        root->left->parent = root;
    }
    else
    {
        root->right = insert(root->right, key);
        root->right->parent = root;
    }
    return root;
}

// find the correct node
node *find(node *root, int key)
{
    if (root == NULL)
        return root;
    if (root->key == key)
        return root;
    if (key < root->key)
        return find(root->left, key);
    return find(root->right, key);
}

// fixup the tree
node *fixup(node *x)
{
    // x is the correct node
    // you always return the root node
    char c;
    node *g, *p, *u, *gg;
    while (x->parent != NULL)
    {
        // x is the current node
        // case 1: no red-red conflict
        if (x->parent->parent == NULL)
        {
            x = x->parent;
            continue;
        }
        if (x->color == 'B' || col(x->parent) == 'B')
        {
            x = x->parent;
            continue;
        }
        // case 2: red-red conflict
        p = x->parent;
        g = p->parent;
        gg = g->parent;
        if (p == g->right)
            u = g->left;
        else
            u = g->right;
        // a) uncle is red
        if (col(u) == 'R')
        {
            g->color = 'R';
            u->color = 'B';
            p->color = 'B';
            x = g;
            continue;
        }
        // b) uncle is black
        if (p == g->left)
        {
            if (x == p->left)
            {
                // LEFT-LEFT
                // swap parent and grand-parent colors
                p->color = 'B';
                g->color = 'R';
            }
            else
            {
                // LEFT-RIGHT
                g->color = 'R';
                x->color = 'B';
                // left rotate p
                g->left = leftRotate(g->left);
            }
            // right rotate g
            if (gg != NULL)
            {

                if (gg->left == g)
                    gg->left = rightRotate(gg->left);
                else
                    gg->right = rightRotate(gg->right);
                x = gg;
            }
            else
                x = rightRotate(g);
            continue;
        }
        else
        {
            if (x == p->right)
            {
                // RIGHT-RIGHT
                // swap parent and grand-parent colors
                p->color = 'B';
                g->color = 'R';
            }
            else
            {
                // RIGHT-LEFT
                g->color = 'R';
                x->color = 'B';
                g->right = rightRotate(g->right);
            }
            if (gg != NULL)
            {
                if (gg->right == g)
                    gg->right = leftRotate(gg->right);
                else
                    gg->left = leftRotate(gg->left);
                x = gg;
            }
            else
                x = leftRotate(g);
            continue;
        }
    }
    x->color = 'B';
    return x;
}

void printTree(node *root)
{
    printf("(");
    if (root != NULL)
    {
        printf("%d %c ", root->key, root->color);
        printTree(root->left);
        printTree(root->right);
    }
    printf(") ");
}

int main()
{
    int k;
    node *root = NULL;
    char s[100];
    scanf("%s", s);
    node *temp;

    while (s[0] != 'e')
    {
        k = atoi(s);
        root = insert(root, k);
        temp = find(root, k);
        root = fixup(temp);
        printTree(root);
        printf("\n");
        scanf("%s", s);
    }
    return 1;
}