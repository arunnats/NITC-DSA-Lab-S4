#include <stdio.h>
#include <stdlib.h>

// Structure to represent a BST node
struct Node
{
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node *newNode(int key)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a key into the BST
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to print key values in the given range
void printRangeValues(struct Node *root, int k1, int k2)
{
    if (root == NULL)
        return;

    if (root->key >= k1 && root->key <= k2)
    {
        printf("%d ", root->key);
    }

    if (root->key > k1)
    {
        printRangeValues(root->left, k1, k2);
    }

    if (root->key < k2)
    {
        printRangeValues(root->right, k1, k2);
    }
}

// Function to print ancestors of a key
void printAncestors(struct Node *root, int key)
{
    if (root == NULL)
        return;

    if (key < root->key)
    {
        printf("%d ", root->key);
        printAncestors(root->left, key);
    }
    else if (key > root->key)
    {
        printf("%d ", root->key);
        printAncestors(root->right, key);
    }
    else
    {
        printf("%d ", root->key);
    }
}

// Function to free memory allocated for the BST
void freeBST(struct Node *root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main()
{
    struct Node *root = NULL;
    char command;
    int key1, key2, key;

    // Read Parenthesis Representation of the tree
    char parenthesis[100];
    scanf("%s", parenthesis);

    // Build the BST based on Parenthesis Representation
    for (int i = 0; parenthesis[i] != '\0'; i++)
    {
        if (parenthesis[i] >= '0' && parenthesis[i] <= '9')
        {
            int key = 0;
            while (parenthesis[i] >= '0' && parenthesis[i] <= '9')
            {
                key = key * 10 + (parenthesis[i] - '0');
                i++;
            }
            root = insert(root, key);
        }
    }

    // Menu-driven program
    do
    {
        scanf(" %c", &command);

        switch (command)
        {
        case 'p':
            scanf("%d %d", &key1, &key2);
            printRangeValues(root, key1, key2);
            printf("\n");
            break;
        case 'a':
            scanf("%d", &key);
            printAncestors(root, key);
            printf("\n");
            break;
        case 'e':
            break;
        default:
            printf("Invalid command\n");
        }
    } while (command != 'e');

    // Free memory allocated for the BST
    freeBST(root);

    return 0;
}
