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

Node *insertFirst(int x, Node *head)
{
    Node *newNode = createNode(x);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    return head;
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

Node *deleteNode(int key, Node *head)
{
    Node *currentNode = head;
    Node *prevNode = NULL;

    while (currentNode != NULL)
    {
        if (currentNode->data == key)
        {
            if (prevNode == NULL)
            {
                head = currentNode->next;
            }
            else
            {
                prevNode->next = currentNode->next;
            }

            free(currentNode);
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
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

Node *reverse(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *rest = reverse(head->next);

    head->next->next = head;
    head->next = NULL;

    return rest;
}

int main()
{
    Node *head = NULL;

    char choice;
    int x;

    do
    {
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'f':
            scanf(" %d", &x);
            head = insertFirst(x, head);
            break;

        case 'l':
            scanf(" %d", &x);
            head = insertLast(x, head);
            break;

        case 'd':
            scanf(" %d", &x);
            head = deleteNode(x, head);
            break;

        case 's':
            display(head);
            break;

        case 'r':
            reverse(head);
            break;

        case 'e':
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 't');

    return 0;
}