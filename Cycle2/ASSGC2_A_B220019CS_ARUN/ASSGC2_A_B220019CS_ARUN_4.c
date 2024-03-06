#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 0
#define BLACK 1

struct Node
{
    int key;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *initializeNode(int key, int color, struct Node *parent)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = color;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

struct Node *buildTree(char ch[], int *i)
{
    int key = 0;
    int c = 0;
    struct Node *root = NULL;
    while (ch[*i] != '\0')
    {
        if (ch[*i] == '(')
        {
            (*i) += 2;
            if (ch[*i] == ')')
            {
                (*i)++;
                return NULL;
            }
            int s = 1;
            if (ch[*i] == '-')
            {
                s = -1;
                (*i)++;
            }
            while (ch[*i] >= '0' && ch[*i] <= '9')
            {
                key = key * 10 + (int)(ch[*i] - '0');
                (*i)++;
            }
            key *= s;
            (*i)++;
            if (ch[*i] == 'R' || ch[*i] == 'r')
            {
                c = RED;
                (*i) += 2;
            }
            if (ch[*i] == 'B' || ch[*i] == 'b')
            {
                c = BLACK;
                (*i) += 2;
            }
            root = initializeNode(key, c, NULL);
            (*i)++;
            root->left = buildTree(ch, i);
            (*i)++;
            root->right = buildTree(ch, i);
            (*i)++;
            return root;
        }
        else if (ch[*i] == ')')
        {
            (*i)++;
            return root;
        }
        else
            (*i)++;
    }
    return root;
}

int checkRedBlackTree(struct Node *root, int count, int *valid)
{
    if (root == NULL)
        return count;

    if (root->color == 1)
        count++;

    if (root->color == 0 && ((root->left && root->left->color == 0) || (root->right && root->right->color == 0)))
        *valid = 0;

    int lc = checkRedBlackTree(root->left, count, valid);
    int rc = checkRedBlackTree(root->right, count, valid);

    if (lc != rc)
        *valid = 0;

    return lc;
}

int main()
{
    char expression[1001];
    fgets(expression, sizeof(expression), stdin);
    size_t len = strlen(expression);

    if (len > 0 && expression[len - 1] == '\n')
    {
        expression[len - 1] = '\0';
        len--;
    }

    int pos = 1;
    struct Node *root = buildTree(expression, &pos);

    int valid = 1;
    int count = 0;

    if (root && root->color == 0)
        valid = 0;
    else
    {
        checkRedBlackTree(root, count, &valid);
    }

    if (valid)
        printf("1\n");
    else
        printf("0\n");

    return 1;
}
