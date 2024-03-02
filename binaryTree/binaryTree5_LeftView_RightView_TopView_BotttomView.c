#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode
{
  int data;
  struct treeNode *left;
  struct treeNode *right;
};

struct QueueNode
{
  struct treeNode *node;
  struct QueueNode *next;
};

struct Queue
{
  int arr[10001];
  int front;
  int rear;
  int size;
};

struct Stack
{
  int arr[10001];
  int top;
};

struct treeNode *createNode(int k)
{
  struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
  newNode->data = k;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void printInOrder(struct treeNode *root)
{
  if (root != NULL)
  {
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
  }
}

struct treeNode *buildTree(int inorder[], int postorder[], int inStart, int inEnd, int *postIndex)
{
  if (inStart > inEnd)
    return NULL;

  struct treeNode *newNode = createNode(postorder[*postIndex]);

  int inIndex;
  for (inIndex = inStart; inIndex <= inEnd; inIndex++)
  {
    if (inorder[inIndex] == newNode->data)
      break;
  }

  (*postIndex)--;

  newNode->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);
  newNode->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
  return newNode;
}

int main()
{
  int n;
  scanf("%d", &n);
  int inorder[n];
  int postorder[n];
  for (int i = 0; i < n; i++)
    scanf("%d", &inorder[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &postorder[i]);
  int postIndex = 0;
  struct treeNode *root = buildTree(inorder, postorder, 0, n - 1, &postIndex);

  printInOrder(root);

  return 1;
}