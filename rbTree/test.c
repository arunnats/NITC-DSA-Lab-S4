#include <stdlib.h>
#include <stdio.h>

struct node
{
    int d;
    int c;
    struct node *right, *left;
};

struct node *createnode(int d, int c)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->d = d;
    new->c = c;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct node *createtree(char ch[], int *i)
{
    int key = 0;
    int c = 0;
    struct node *root = NULL;
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
                c = 0;
                (*i) += 2;
            }
            if (ch[*i] == 'B' || ch[*i] == 'b')
            {
                c = 1;
                (*i) += 2;
            }
            root = createnode(key, c);
            root->left = createtree(ch, i);
            root->right = createtree(ch, i);
            while (ch[*i] != ')')
                (*i)++;
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

int check(struct node *tree, int count, int *valid)
{
    if (tree == NULL)
        return count;
    if (tree->c == 1)
        count++;
    if (tree->c == 0 && ((tree->left && tree->left->c == 0) || (tree->right && tree->right->c == 0)))
        *valid = 0;
    int lc = check(tree->left, count, valid);
    int rc = check(tree->right, count, valid);
    if (lc != rc)
        *valid = 0;
    return lc;
}

void inorderTraversal(struct node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("(%d %d)", root->d, root->c);
        inorderTraversal(root->right);
    }
}

int main()
{
    char ch[500];
    fgets(ch, 500, stdin);
    struct node *tree = NULL;
    int c = 0;
    tree = createtree(ch, &c);
    int valid = 1;
    int count = 0;

    printf("In-order traversal of the constructed RB Tree:\n");
    inorderTraversal(tree);
    printf("\n");

    if (tree->c == 0)
        valid = 0;
    else
    {
        check(tree, count, &valid);
    }
    if (valid)
        printf("1\n");
    else
        printf("0\n");
    return 0;
}