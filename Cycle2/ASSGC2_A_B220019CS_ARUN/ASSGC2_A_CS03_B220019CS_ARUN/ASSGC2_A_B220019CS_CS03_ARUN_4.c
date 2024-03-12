#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int key;
    int colour;
    struct Node *right, *left;
};

struct Node *createNode(int key, int colour)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->colour = colour;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *buildTree(char expression[], int *i)
{
    int key = 0;
    int colour = 0;
    struct Node *root = NULL;
    while (expression[*i] != '\0')
    {
        if (expression[*i] == '(')
        {
            (*i) += 2;
            if (expression[*i] == ')')
            {
                (*i)++;
                return NULL;
            }
            int s = 1;
            if (expression[*i] == '-')
            {
                s = -1;
                (*i)++;
            }
            while (expression[*i] >= '0' && expression[*i] <= '9')
            {
                key = key * 10 + (int)(expression[*i] - '0');
                (*i)++;
            }
            key *= s;
            (*i)++;
            if (expression[*i] == 'R' || expression[*i] == 'r')
            {
                colour = 0;
                (*i) += 2;
            }
            if (expression[*i] == 'B' || expression[*i] == 'b')
            {
                colour = 1;
                (*i) += 2;
            }
            root = createNode(key, colour);
            root->left = buildTree(expression, i);
            root->right = buildTree(expression, i);
            while (expression[*i] != ')')
                (*i)++;
        }
        else if (expression[*i] == ')')
        {
            (*i)++;
            return root;
        }
        else
            (*i)++;
    }
    return root;
}

int checkRBCondition(struct Node *root, int count, int *valid)
{
    if (root == NULL)
        return count;
    if (root->colour == 1)
        count++;
    if (root->colour == 0 && ((root->left && root->left->colour == 0) || (root->right && root->right->colour == 0)))
        *valid = 0;
    int lc = checkRBCondition(root->left, count, valid);
    int rc = checkRBCondition(root->right, count, valid);
    if (lc != rc)
        *valid = 0;
    return lc;
}

int main()
{
    char expression[1001];
    fgets(expression, 1001, stdin);

    struct Node *root = NULL;

    int colour = 0;
    root = buildTree(expression, &colour);
    int valid = 1;
    int count = 0;
    if (root->colour == 0)
        valid = 0;
    else
    {
        checkRBCondition(root, count, &valid);
    }
    if (valid)
        printf("1\n");
    else
        printf("0\n");
    return 0;
}