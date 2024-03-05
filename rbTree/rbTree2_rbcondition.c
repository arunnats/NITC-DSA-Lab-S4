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

// struct Node *buildTree(char *expression)
// {
//     struct Node *root = NULL;
//     struct Node *current = NULL;
//     struct Node *queue[1001];
//     int front = -1;
//     int rear = -1;

//     int pos = 0;
//     while (expression[pos] != '\0')
//     {
//         int num = 0;
//         while (expression[pos] != ' ' && expression[pos] != '\0')
//         {
//             num = num * 10 + (expression[pos] - '0');
//             pos++;
//         }

//         char colorChar = expression[++pos];
//         int color = (colorChar == 'B') ? BLACK : RED;

//         struct Node *newNode = initializeNode(num, color);

//         if (root == NULL)
//         {
//             root = newNode;
//             current = root;
//         }
//         else
//         {
//             if (current->l == NULL)
//             {
//                 current->l = newNode;
//             }
//             else if (current->r == NULL)
//             {
//                 current->r = newNode;
//             }

//             if (current->l != NULL && current->r != NULL)
//             {
//                 front++;
//                 current = queue[front];
//             }
//         }

//         if (expression[++pos] == '(')
//         {
//             queue[++rear] = newNode;
//             pos++;
//         }
//     }

//     return root;
// }

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
                c = 0;
                (*i) += 2;
            }
            if (ch[*i] == 'B' || ch[*i] == 'b')
            {
                c = 1;
                (*i) += 2;
            }
            root = initializeNode(key, c);
            (*i)++;
            root->l = buildTree(ch, i);
            (*i)++;
            root->r = buildTree(ch, i);
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

// struct Node *buildTree(char *expression, int *pos)
// {
//     while (expression[*pos] == ' ')
//     {
//         (*pos)++;
//     }

//     if (expression[*pos] == '\0' || expression[*pos] == ')')
//     {
//         return NULL;
//     }

//     int num = 0;
//     while (expression[*pos] >= '0' && expression[*pos] <= '9')
//     {
//         num = num * 10 + (expression[*pos] - '0');
//         (*pos)++;
//     }

//     while (expression[*pos] == ' ')
//     {
//         (*pos)++;
//     }

//     char colorChar = expression[*pos];
//     int color = (colorChar == 'B') ? BLACK : RED;

//     struct Node *root = initializeNode(num, color);

//     (*pos)++;

//     if (expression[*pos] == '(')
//     {
//         (*pos)++;

//         root->l = buildTree(expression, pos);

//         (*pos)++;
//     }

//     if (expression[*pos] == '(')
//     {
//         (*pos)++;

//         root->r = buildTree(expression, pos);

//         (*pos)++;
//     }

//     return root;
// }

void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->l);
        printf("(%d %d)", root->key, root->color);
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
    // char expression[1001];
    // fgets(expression, sizeof(expression), stdin);
    // size_t len = strlen(expression);

    // if (len > 0 && expression[len - 1] == '\n')
    // {
    //     expression[len - 1] = '\0';
    //     len--;
    // }

    // struct Node *root = buildTree(expression);

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
