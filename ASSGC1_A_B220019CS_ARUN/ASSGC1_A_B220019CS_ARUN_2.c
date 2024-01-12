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

Node *listInsert(int x, Node *head)
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

Node *listDelete(int key, Node *head)
{
    if (head == NULL)
    {
        return head;
    }
    else
    {
        Node *currentNode = head;
        Node *prevNode = NULL;
        while (currentNode != NULL)
        {
            if (currentNode->data == key)
            {
                prevNode->next = currentNode->next;
                free(currentNode);
                break;
            }

            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        return head;
    }
}

void listDisplay(Node *head)
{
    Node *currentNode = head;

    while (currentNode != NULL)
    {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
}
