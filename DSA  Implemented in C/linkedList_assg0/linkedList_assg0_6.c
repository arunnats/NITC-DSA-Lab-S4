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

Node *reverseK(Node *head, int k)
{
}

int main()
{
    int n, k;
    Node *head = NULL;

    printf("Enter number of elements in the linked list: ");
    scanf("%d", &n);
    printf("Enter number of elements to reverse by: ");
    scanf("%d", &k);
    head = linkedListInput(n);
    head = reverseK(head, k);
    printf("Sorted k reversed list: ");
    display(head);

    return 0;
}
