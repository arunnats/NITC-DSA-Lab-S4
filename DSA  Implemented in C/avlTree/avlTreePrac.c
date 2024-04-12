#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

struct Node *newNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int balance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return (node->left->height) - (node->right->height);
}

struct Node *rotateRight(struct Node *x)
{
    struct Node *y = x->left;
    struct Node *z = y->right;

    y->right = x;
    x->left = z;

    y->height = (max(y->left->height, y->left->height) + 1);
    x->height = (max(x->left->height, x->left->height) + 1);

    return y;
}

struct Node *rotateLeft(struct Node *x)
{
    struct Node *y = x->left;
    struct Node *z = y->right;

    y->left = x;
    x->right = z;

    y->height = (max(y->left->height, y->left->height) + 1);
    x->height = (max(x->left->height, x->left->height) + 1);

    return y;
}

struct Node *findSuccessor(struct Node *node, struct Node *root)
{
    if (node->right != NULL)
    {
        struct Node *succ = node->right;
        while (succ->left != NULL)
            succ = succ->left;
        return succ;
    }

    struct Node *succ = NULL;
    struct Node *curr = root;

    while (curr != NULL)
    {
        if (node->key < curr->key)
        {
            succ = curr;
            curr = curr->left;
        }
        else if (node->key > curr->key)
        {
            curr = curr->right;
        }
        else
        {
            break;
        }
    }
    return succ;
}

struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
    {
        return newNode(key);
    }

    if (key > root->key)
        root->right = insert(root->right, key);
    else
        root->left = insert(root->left, key);

    root->height = (max(root->left->height, root->left->height) + 1);

    if (balance(root) > 1 && key < root->left->key)
    {
        return rotateRight(root);
    }

    if (balance(root) < 1 && key > root->right->key)
    {
        return rotateLeft(root);
    }

    if (balance(root) > 1 && key > root->left->key)
    {
        root->left = rotateLeft(root->left);
        return root = rotateRight(root);
    }

    if (balance(root) < 1 && key < root->right->key)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

struct Node *delete(struct Node *root, int key, struct Node *rootPerm)
{
    if (root == NULL)
    {
        printf("-1\n");
        return NULL;
    }

    if (key > root->key)
        delete (root->right, key, root);

    else if (key < root->key)
        delete (root->left, key, root);

    else
    {
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            root = NULL;
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            root = NULL;
            return temp;
        }

        else
        {
            struct Node *temp = findSuccessor(root, rootPerm);
            root = temp;
            delete (rootPerm, temp->key, rootPerm);
        }
    }

    root->height = (max(root->left->height, root->left->height) + 1);

    if (balance(root) > 1 && balance(root->left) >= 0)
    {
        rotateRight(root);
    }

    if (balance(root) < 1 && balance(root->right) <= 0)
    {
        rotateLeft(root);
    }

    if (balance(root) > 1 && balance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        root = rotateRight(root);
    }

    if (balance(root) < 1 && balance(root->left) > 0)
    {
        root->right = rotateRight(root->right);
        rotateLeft(root);
    }

    return root;
}

void printParenthesisRep(struct Node *node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }

    printf("(%d ", node->key);
    printParenthesisRep(node->left);
    printParenthesisRep(node->right);
    printf(") ");
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
            scanf(" %d", &key);
            root = insert(root, key);
            printParenthesisRep(root);
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
