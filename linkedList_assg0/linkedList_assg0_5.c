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

int main()
{
    int n1, n2;
    Node *head1 = NULL, *head2 = NULL;

    printf("Enter number of elements in the first sorted linked list: ");
    scanf("%d", &n1);
    head1 = linkedListInput(n1);

    printf("Enter number of elements in the second sorted linked list: ");
    scanf("%d", &n2);
    head2 = linkedListInput(n2);

    Node *head = NULL;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data < head2->data)
        {
            head = insertLast(head1->data, head);
            head1 = head1->next;
        }
        else
        {
            head = insertLast(head2->data, head);
            head2 = head2->next;
        }
    }

    while (head1 != NULL)
    {
        head = insertLast(head1->data, head);
        head1 = head1->next;
    }

    while (head2 != NULL)
    {
        head = insertLast(head2->data, head);
        head2 = head2->next;
    }

    printf("Merged linked list: ");
    display(head);

    return 0;
}
