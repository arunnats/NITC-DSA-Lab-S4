#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct node
{
    int val;
    char color;
    struct node *left;
    struct node *right;
};

typedef struct node node;

node *createNode(int val)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->val = val;
    nn->color = 'R';
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}
// criteria for red-black tree
// root black
// no red-red conflict
// black height should be same in all directions from root

char col(node *root)
{
    if (root == NULL)
        return 'B';
    return root->color;
}

node *construct(char *arr, int *i)
{
    // we always start at an opening brace
    (*i)++;
    if (arr[*i] == ')')
    {
        (*i)++;
        return NULL;
    }
    int k = 0;
    while (arr[*i] >= 48 && arr[*i] <= 57)
    {
        k *= 10;
        k += arr[*i] - 48;
        (*i)++;
    }
    node *root = createNode(k);
    root->color = arr[*i];
    (*i)++;
    // root is created
    root->left = construct(arr, i);
    root->right = construct(arr, i);
    (*i)++;
    return root;
}

void preorder(node *root)
{
    if (root != NULL)
    {
        printf("%d %c ", root->val, root->color);
        preorder(root->left);
        preorder(root->right);
    }
    return;
}

int leftheight(node *root)
{
    if (root == NULL)
        return 1;
    int a = (root->color == 'B') ? 1 : 0;
    return a + leftheight(root->left);
}

int validateRB(node *root, int h, int lh)
{
    if (root == NULL)
    {
        h += 1;
        // printf("%d ",h);
        if (h != lh)
            return 0;
        return 1;
    }
    if (col(root) == 'R' && (col(root->right) == 'R' || col(root->left) == 'R'))
        return 0;
    int a = (root->color == 'B') ? 1 : 0;

    int l = validateRB(root->left, h + a, lh);
    int r = validateRB(root->right, h + a, lh);
    if (l == 1 && r == 1)
        return 1;
    return 0;
}

int findMax(node *root)
{
    if (root == NULL)
        return INT_MIN;
    if (root->right == NULL)
        return root->val;
    return findMax(root->right);
}

int findMin(node *root)
{
    if (root == NULL)
        return INT_MAX;
    if (root->left == NULL)
        return root->val;
    return findMin(root->left);
}
int validBST(node *root)
{
    if (root == NULL)
        return 1;
    int l = findMax(root->left);
    int r = findMin(root->right);
    if (l >= root->val || r <= root->val)
        return 0;
    l = validBST(root->left);
    r = validBST(root->right);
    if (l == 0 || r == 0)
        return 0;
    return 1;
}
int main()
{
    char s[1000];
    scanf("%[^\n]s", s);
    char p[1000];
    int n = strlen(s);
    int i;
    int j = 0;

    for (i = 0; i < n; i++)
    {
        if (s[i] == ' ')
            continue;
        p[j++] = s[i];
    }
    p[j] = '\0';
    int t[1] = {0};
    node *root = construct(p, t);
    int lh = leftheight(root);
    int vRB = validateRB(root, 0, lh);
    if (validBST(root) && vRB == 1)
        vRB = 1;
    else
        vRB = 0;
    printf("%d\n", vRB);
    return 1;
}