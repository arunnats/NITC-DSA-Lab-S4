#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 0
#define BLACK 1

struct Node
{
    int key;
    int color;
    struct Node *l;
    struct Node *r;
    struct Node *p;
};

struct Node *initializeNode(int key, int color)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = color;
    newNode->l = newNode->r = newNode->p = NULL;
    return newNode;
}

struct Node *buildRBTree(char *expression, int start, int end)
{
    if (start > end)
        return NULL;

    int num = 0;
    while (start <= end && expression[start] >= '0' && expression[start] <= '9')
    {
        num *= 10;
        num += (expression[start] - '0');
        start++;
    }

    char color = expression[start + 1];

    struct Node *root = initializeNode(num, (color == 'B') ? BLACK : RED);

    int count = 0;
    int index = -1;

    for (int i = start; i <= end; i++)
    {
        if (expression[i] == '(')
            count++;
        else if (expression[i] == ')')
            count--;

        if (count == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        root->l = buildRBTree(expression, start + 3, index - 1);
        root->r = buildRBTree(expression, index + 2, end - 1);
    }

    return root;
}

void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->l);
        printf("%d %c", root->key);
        inorderTraversal(root->r);
    }
}

int checkBlackHeight(struct Node *node)
{
    if (node == NULL)
        return 1;

    int leftHeight = checkBlackHeight(node->l);
    int rightHeight = checkBlackHeight(node->r);

    if (leftHeight == rightHeight)
    {
        if (node->color == BLACK)
            return leftHeight + 1;
        else
            return leftHeight;
    }
    else
    {
        return 0;
    }
}

int checkRedblackTree(struct Node *root)
{
    if (root != NULL && root->color != BLACK)
        return 0;

    if (root == NULL || (root->color != RED && root->color != BLACK))
        return 1;

    if (root->color == RED && (root->l == NULL || root->r == NULL))
        return 0;

    return checkBlackHeight(root);
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

    struct Node *root = buildRBTree(expression, 1, sizeof(expression) / sizeof(expression[0]) - 2);

    printf("In-order traversal of the constructed RB Tree:\n");
    inorderTraversal(root);
    printf("\n");

    int isRedBlackTree = checkRedblackTree(root);

    if (isRedBlackTree)
        printf("The tree is a red-black tree.\n");
    else
        printf("The tree is not a red-black tree.\n");

    return 0;
}
