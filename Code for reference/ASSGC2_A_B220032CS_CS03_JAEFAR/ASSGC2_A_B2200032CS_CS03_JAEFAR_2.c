#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// insert into avl tree
// if the key exists, update the corresponding value
// lower_bound

struct node
{
    int key;
    int val;
    int height;
    struct node *left;
    struct node *right;
};

typedef struct node node;
node *createNode(int key, int val)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->key = key;
    nn->val = val;
    nn->height = 0;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

void heightify(node *root)
{
    int l = -1;
    int r = -1;
    if (root->left != NULL)
        l = root->left->height;
    if (root->right != NULL)
        r = root->right->height;
    int h = l;
    if (r > h)
        h = r;
    root->height = h + 1;
    return;
}

int calcBF(node *root)
{
    int l = -1;
    int r = -1;
    if (root->left != NULL)
        l = root->left->height;
    if (root->right != NULL)
        r = root->right->height;
    return l - r;
}

node *leftRotate(node *z)
{
    node *y = z->right;
    z->right = y->left;
    y->left = z;
    heightify(z);
    heightify(y);
    return y;
}

node *rightRotate(node *z)
{
    node *y = z->left;
    z->left = y->right;
    y->right = z;
    heightify(z);
    heightify(y);
    return y;
}
node *insert(node *root, int key, int val)
{
    // inserting the node
    if (root == NULL)
        return createNode(key, val);
    if (key == root->key)
    {
        root->val = val;
        return root;
    }
    else if (key < root->key)
        root->left = insert(root->left, key, val);
    else
        root->right = insert(root->right, key, val);
    // set heights
    heightify(root);
    // check for imbalance
    // first find balance factor
    int bf = calcBF(root);
    if (bf > -2 && bf < 2)
        return root;
    // there is an imbalance, bf is -2 or +2
    node *z = root;
    node *y, *x;
    if (bf == 2)
        y = root->left;
    else
        y = root->right;
    bf = calcBF(y);
    if (bf == 1)
        x = root->left;
    else
        x = root->right;
    // now you have z, y and x
    if (y == z->left)
    {
        if (x == y->right)
        {
            y = leftRotate(y);
        }
        z = rightRotate(z);
    }
    else
    {
        if (x == y->left)
        {
            y = rightRotate(y);
        }
        z = leftRotate(z);
    }
    return z;
}

// lower_bound,
node *lower_bound(node *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->key < key)
    {
        return lower_bound(root->right, key);
    }
    // key>=root->key
    // first search the left subtree, then the right subtree
    if (root->left != NULL && root->left->key >= key)
        return lower_bound(root->left, key);
    return root;
}

// find
node *find(node *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root;
    if (key < root->key)
        return find(root->left, key);
    return find(root->right, key);
}

// size
int size(node *root)
{
    if (root == NULL)
        return 0;
    return 1 + size(root->left) + size(root->right);
}

// empty
int empty(node *root)
{
    if (root == NULL)
        return 1;
    return 0;
}

void printElements(node *root)
{
    if (root != NULL)
    {
        printElements(root->left);
        printf("%d ", root->key);
        printElements(root->right);
    }
    return;
}

int main()
{
    char s[2];
    int k, v;
    scanf("%s", s);
    char c;
    node *root = NULL;
    node *temp;
    while (s[0] != 't')
    {
        c = s[0];
        if (c == 'i')
        {
            scanf("%d %d", &k, &v);
            root = insert(root, k, v);
        }
        else if (c == 'l')
        {
            scanf("%d", &k);
            temp = lower_bound(root, k);
            if (temp == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d %d\n", temp->key, temp->val);
            }
        }
        else if (c == 'f')
        {
            scanf("%d", &k);
            temp = find(root, k);
            if (temp == NULL)
                printf("-1\n");
            else
            {
                printf("%d %d\n", temp->key, temp->val);
            }
        }
        else if (c == 's')
        {
            printf("%d\n", size(root));
        }
        else if (c == 'e')
        {
            printf("%d\n", empty(root));
        }
        else if (c == 'p')
        {
            if (root == NULL)
                printf("-1");
            else
                printElements(root);
            printf("\n");
        }
        scanf("%s", s);
    }
    return 1;
}