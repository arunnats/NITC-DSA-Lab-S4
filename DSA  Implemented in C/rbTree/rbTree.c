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

struct Node *fix(struct Node *root, struct Node *z)
{
    while (z != root && z->parent->colour == 0) // While the parent of z is red
    {
        if (z->parent == z->parent->parent->left) // If the parent of z is a left child
        {
            struct Node *y = z->parent->parent->right; // Uncle of z
            if (y != NULL && y->colour == 0)           // Case 1: Uncle is red
            {
                z->parent->colour = 1;         // Change the colour of parent to black
                y->colour = 1;                 // Change the colour of uncle to black
                z->parent->parent->colour = 0; // Change the colour of grandparent to red
                z = z->parent->parent;         // Move z up to the grandparent
            }
            else // Case 2 & 3: Uncle is black or NULL
            {
                if (z == z->parent->right) // Case 2: z is a right child
                {
                    z = z->parent;        // Move z up to its parent
                    leftRotate(&root, z); // Perform left rotation
                }
                // Case 3: z is a left child
                z->parent->colour = 1;                 // Change the colour of parent to black
                z->parent->parent->colour = 0;         // Change the colour of grandparent to red
                rightRotate(&root, z->parent->parent); // Perform right rotation
            }
        }
        else // If the parent of z is a right child (symmetric to the left case)
        {
            struct Node *y = z->parent->parent->left; // Uncle of z
            if (y != NULL && y->colour == 0)          // Case 1: Uncle is red
            {
                z->parent->colour = 1;
                y->colour = 1;
                z->parent->parent->colour = 0;
                z = z->parent->parent;
            }
            else // Case 2 & 3: Uncle is black or NULL
            {
                if (z == z->parent->left) // Case 2: z is a left child
                {
                    z = z->parent;
                    rightRotate(&root, z);
                }
                // Case 3: z is a right child
                z->parent->colour = 1;
                z->parent->parent->colour = 0;
                leftRotate(&root, z->parent->parent);
            }
        }
    }
    root->colour = 1; // Set the root to black to maintain the property
    return root;
}

struct Node *insert(struct Node *root, int num)
{

    struct Node *z = createNode(num, 0, NULL);

    if (root == NULL)
        return z;

    struct Node *parent = NULL;
    struct Node *current = root;
    while (current != NULL)
    {
        parent = current;
        if (num < current->key)
            current = current->left;
        else
            current = current->right;
    }

    z->parent = parent;
    if (num < parent->key)
        parent->left = z;
    else
        parent->right = z;

    return fix(root, z);
}

void printParenthesisRep(struct Node *node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }

    printf("(%d %c ", node->key, (node->colour == 0) ? 'R' : 'B');
    printParenthesisRep(node->left);
    printParenthesisRep(node->right);
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
        root = insert(root, x);
        printParenthesisRep(root);
        printf("\n");
    }

    return 1;
}
