#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node Node;

struct stack
{
    int data[101];
    int top;
};

typedef struct stack Stack;

void push(Stack *S, int x)
{
    S->data[S->top++] = x;
}

int pop(Stack *S)
{
    return S->data[S->top--];
}

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

Node *listDelete(int index, Node *head)
{
    if (head == NULL || index <= 0)
    {
        return head;
    }

    if (index == 1)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node *currentNode = head;
    Node *prevNode = NULL;
    int count = 1;

    while (currentNode != NULL && count < index)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
        count++;
    }

    if (currentNode == NULL)
    {
        printf("-1\n");
        return head;
    }

    prevNode->next = currentNode->next;
    printf("%d\n", currentNode->data);
    free(currentNode);
    return head;
}

void listDisplay(Node *head)
{
    Node *currentNode = head;

    while (currentNode != NULL)
    {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

Node *reverse(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *newHead = NULL;
    Node *current = head;

    while (current != NULL)
    {
        Node *newNode = createNode(current->data);
        newNode->next = newHead;
        newHead = newNode;
        current = current->next;
    }

    return newHead;
}

int listPal(Node *head)
{
    Node *reversed = reverse(head);
    Node *currentNode = head;
    Node *currentReversedNode = reversed;

    while (currentNode != NULL)
    {
        if (currentNode->data != currentReversedNode->data)
        {
            return 0;
        }
        currentNode = currentNode->next;
        currentReversedNode = currentReversedNode->next;
    }
    return 1;
}

Node *deleteAll(Node *head, int x)
{
    Node *currentNode = head;
    Node *prevNode = NULL;

    while (currentNode != NULL)
    {
        if (currentNode->data == x)
        {
            if (prevNode == NULL)
            {
                head = currentNode->next;
            }
            else
            {
                prevNode->next = currentNode->next;
            }

            Node *temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
        else
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    return head;
}

Node *rDuplicate(Node *head)
{
    Node *currentNode = head;

    while (currentNode != NULL)
    {
        currentNode->next = deleteAll(currentNode->next, currentNode->data);
        currentNode = currentNode->next;
    }

    return head;
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
        case 'a':
            scanf(" %d", &x);
            head = listInsert(x, head);
            break;

        case 'r':
            scanf(" %d", &x);
            head = listDelete(x, head);
            break;

        case 'd':
            head = rDuplicate(head);
            listDisplay(head);
            break;

        case 'p':
            if (listPal(head))
                printf("Y\n");
            else
                printf("N\n");
            break;

        case 's':
            listDisplay(head);
            break;

            /*case 'o':
                Node *temp = reverse(head);
                listDisplay(temp);
                break;*/

        default:
            break;
        }

    } while (choice != 'e');

    return 1;
}
