#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node Node;

Node *createNode(int x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

Node *insertLast(int x, Node *head)
{
    Node *newNode = createNode(x);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *tempNode = head;
        while (tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
    return head;
}

Node *linkedListInput(int n)
{
    Node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        head = insertLast(x, head);
    }
    return head;
}

void display(Node *head)
{
    Node *currentNode = head;

    while (currentNode != NULL)
    {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
}

Node *swap(Node *head, int key1, int key2)
{
    Node *keyNode1 = NULL;
    Node *keyNode2 = NULL;
    Node *currentNode = head;

    while (currentNode != NULL)
    {
        if (currentNode->data == key1)
        {
            keyNode1 = currentNode;
        }
        else if (currentNode->data == key2)
        {
            keyNode2 = currentNode;
        }
        currentNode = currentNode->next;
    }

    if (keyNode1 != NULL && keyNode2 != NULL)
    {
        int temp = keyNode1->data;
        keyNode1->data = keyNode2->data;
        keyNode2->data = temp;
    }

    return head;
}

int main()
{
    int n;
    Node *head = NULL;

    printf("Enter number of elements in the linked list: ");
    scanf("%d", &n);
    head = linkedListInput(n);

    printf("Sorted linked list: ");
    display(head);

    return 0;
}
