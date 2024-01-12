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


int listPal(Node* head)
{
    Stack S;
    S.top = -1;
    
    Node* currentNode = head;
    
    while(currentNode != NULL)
    {
        push(&S, currentNode->data);
        currentNode = currentNode -> next;   
    }
    
    while(currentNode != NULL)
    {
        int temp = pop(&S);
        
        if(currentNode->data != temp)
        {
            return 0;
        }
        
        currentNode = currentNode -> next;   
    }
    return 1;
}


Node* deleteAll(Node* head, int x)
{
    Node* nextNode = head->next;
    Node* currentNode = head;    
    Node* prevNode = NULL;    
    
    if(currentNode->data == x)
    {
        head = nextNode;
        free(currentNode);   
        
        prevNode = currentNode;
        currentNode = currentNode -> next;
        nextNode = currentNode -> next -> next;  
    }
    
    while(currentNode != NULL)
    {
        if(currentNode->data == x)
        {
            prevNode->next = nextNode;
            free(currentNode);      
        }
        prevNode = currentNode;
        currentNode = currentNode -> next;
        nextNode = currentNode -> next -> next;   
    }
    
    return head;
}

Node* rDuplicate(Node* head)
{
    Node* currentNode = head;
    
    while(currentNode != NULL)
    {
        currentNode -> next = deleteAll(currentNode->next,currentNode->data);
        currentNode = currentNode -> next;   
    }
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
            if(listPal)
                printf("Y\n");
            else
                printf("N\n");
            break;
        
        case 's':
            listDisplay(head);
            break;

        default:
            break
        }

    } while (choice != 'e');

    return 0;
}
