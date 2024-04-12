#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

/*ou are given a sequence of operations to perform on an AVL tree. Each operation is represented
by a character followed by its respective parameters. The operations are as follows: [ i , x , p , s ,
e]
Input format:
• Each line contains a character from ‘i’, ‘x’, ‘p’, ‘s’, ‘e’ followed by zero or one integers. The
integers, if given, are in the range ∈ [1, 106].
• i: AVL insert(T, key) - Insert the given key into the AVL tree T.
• x: AVL find(T, key) - Search for the given key in the AVL tree T. If the key is found, print
the path from the root to the node containing the key; otherwise, print -1.
• p: AVL preorder(T) - Print the preorder traversal of the AVL tree T.
• s: AVL cal(T) - Given a point, calculate the total number of left and right rotations required
to balance the AVL tree T at that point. left rotation, right rotation separated by space
• e: Exit - Terminate the sequence of operations.
NOTE : key ∈ [1, 106*/

struct node
{
	int val;
	int height;
	struct node *left;
	struct node *right;
};

typedef struct node node;

node *createNode(int val)
{
	node *nn = (node *)malloc(sizeof(node));
	nn->val = val;
	nn->height = 0;
	nn->left = NULL;
	nn->right = NULL;
	return nn;
}

void heightify(node *root)
{
	if (root == NULL)
		return;
	int h = -1;
	if (root->left != NULL && root->left->height > h)
		h = root->left->height;
	if (root->right != NULL && root->right->height > h)
		h = root->right->height;
	root->height = 1 + h;
	return;
}

int bf(node *root)
{
	if (root == NULL)
		return 0;
	int l = -1;
	int r = -1;
	if (root->left != NULL)
		l = root->left->height;
	if (root->right != NULL)
		r = root->right->height;
	return l - r;
}

// LL - rotate right
// LR - rotate y left, rotate z right
// RR - rotate left
// RL - rotate y right, rotate z left

node *leftRotate(node *root)
{
	node *z = root;
	node *y = root->right;
	z->right = y->left;
	y->left = z;
	heightify(z);
	heightify(y);
	return y;
}
node *rightRotate(node *root)
{
	// to rotate
	node *z = root;
	node *y = z->left;
	z->left = y->right;
	y->right = z;

	heightify(z);
	heightify(y);
	return y;
}
node *insert(node *root, int val, int *lcount, int *rcount)
{

	// if root is NULL
	if (root == NULL)
		return createNode(val);
	// where to initially insert
	if (val < root->val)
		root->left = insert(root->left, val, lcount, rcount);
	else
		root->right = insert(root->right, val, lcount, rcount);
	// update the heights
	heightify(root);
	// balance factor
	int bal = bf(root);

	if (bal < 2 && bal > -2)
		return root;
	// first unbalanced node
	node *z, *x, *y;
	z = root;
	y = (bal == 2) ? z->left : z->right;
	bal = bf(y);
	x = (bal > 0) ? y->left : y->right;
	if (y == z->left)
	{
		if (x == y->right)
		{
			z->left = leftRotate(y);
			(*lcount)++;
		}
		z = rightRotate(z);
		(*rcount)++;
	}
	else
	{
		if (x == y->left)
		{
			z->right = rightRotate(y);
			(*rcount)++;
		}
		z = leftRotate(z);
		(*lcount)++;
	}
	return z;
}

node *search(node *root, int key)
{
	if (root == NULL)
		return NULL;
	if (root->val == key)
		return root;
	if (key < root->val)
		return search(root->left, key);
	return search(root->right, key);
}

void printPath(node *root, int key)
{
	if (root == NULL)
		return;
	printf("%d ", root->val);
	if (key == root->val)
		return;
	if (key < root->val)
		printPath(root->left, key);
	else
		printPath(root->right, key);
	return;
}

void find(node *root, int key)
{
	node *check = search(root, key);
	if (check == NULL)
		printf("-1");
	else
		printPath(root, key);
	printf("\n");
	return;
}

void preorder(node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->val);
		preorder(root->left);
		preorder(root->right);
	}
	return;
}

int main()
{
	char s[2];
	char c;
	node *root = NULL;
	int lcount[1] = {0};
	int rcount[1] = {0};
	scanf("%s", s);
	int k;
	while (s[0] != 'e')
	{
		c = s[0];
		if (c == 'i')
		{
			scanf("%d", &k);
			root = insert(root, k, lcount, rcount);
		}
		else if (c == 'x')
		{
			scanf("%d", &k);
			find(root, k);
		}
		else if (c == 'p')
		{
			preorder(root);
			printf("\n");
		}
		else if (c == 's')
		{
			printf("%d %d\n", *lcount, *rcount);
		}
		scanf("%s", s);
	}
	return 0;
}
