#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    char name[1001];
    int priority;
    char admitTime[1001];
};

struct Node
{
    struct Patient patient;
    struct Node *next;
};

struct pQueue
{
    struct Node *front;
};

struct pQueue *initializePriorityQueue()
{
    struct pQueue *priorityQueue = (struct pQueue *)malloc(sizeof(struct pQueue));
    priorityQueue->front = NULL;
    return priorityQueue;
}

void insertHeap(struct pQueue *priorityQueue, struct Patient newPatient)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->patient = newPatient;
    newNode->next = NULL;

    if (priorityQueue->front == NULL || newPatient.priority > priorityQueue->front->patient.priority ||
        (newPatient.priority == priorityQueue->front->patient.priority && strcmp(newPatient.admitTime, priorityQueue->front->patient.admitTime) < 0))
    {
        newNode->next = priorityQueue->front;
        priorityQueue->front = newNode;
    }
    else
    {
        struct Node *current = priorityQueue->front;
        while (current->next != NULL && (newPatient.priority < current->next->patient.priority || (newPatient.priority == current->next->patient.priority && strcmp(newPatient.admitTime, current->next->patient.admitTime) >= 0)))
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void removeHeap(struct pQueue *priorityQueue)
{
    if (priorityQueue->front == NULL)
    {
        printf("-1\n");
        return;
    }

    struct Node *temp = priorityQueue->front;
    priorityQueue->front = priorityQueue->front->next;
    free(temp);

    printf("Patient treated and removed from the queue.\n");
}

void admitPatient(struct pQueue *priorityQueue, char *name, int priority, char *admitTime)
{
    struct Patient newPatient;
    strcpy(newPatient.name, name);
    newPatient.priority = priority;
    strcpy(newPatient.admitTime, admitTime);

    insertHeap(priorityQueue, newPatient);
}

void treatNextPatient(struct pQueue *priorityQueue)
{
    if (priorityQueue->front == NULL)
    {
        printf("-1\n");
    }
    else
    {
        printf("%s %d %s\n", priorityQueue->front->patient.name, priorityQueue->front->patient.priority, priorityQueue->front->patient.admitTime);
        removeHeap(priorityQueue);
    }
}

void checkNextPatient(struct pQueue *priorityQueue)
{
    if (priorityQueue->front == NULL)
    {
        printf("-1\n");
    }
    else
    {
        printf("%s %d %s\n", priorityQueue->front->patient.name, priorityQueue->front->patient.priority, priorityQueue->front->patient.admitTime);
    }
}

void dischargePatient(struct pQueue *priorityQueue, char *name, char *admitTime)
{
    if (priorityQueue->front == NULL)
    {
        printf("-1\n");
        return;
    }

    struct Node *current = priorityQueue->front;
    struct Node *prev = NULL;

    while (current != NULL && (strcmp(current->patient.name, name) != 0 || strcmp(current->patient.admitTime, admitTime) != 0))
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("-1\n");
    }
    else
    {
        if (prev == NULL)
        {
            priorityQueue->front = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        free(current);
        printf("%s %d %s\n", name, current->patient.priority, admitTime);
    }
}

void updateConditionSeverity(struct pQueue *priorityQueue, char *name, char *admitTime, int newPriority)
{
    if (priorityQueue->front == NULL)
    {
        printf("-1\n");
        return;
    }

    struct Node *current = priorityQueue->front;
    struct Node *prev = NULL;

    while (current != NULL && (strcmp(current->patient.name, name) != 0 || strcmp(current->patient.admitTime, admitTime) != 0))
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("-1\n");
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->patient = current->patient;
        newNode->patient.priority = newPriority;
        newNode->next = current->next;

        if (prev == NULL)
        {
            priorityQueue->front = newNode;
        }
        else
        {
            prev->next = newNode;
        }

        free(current);
        printf("%s %s.\n", name, admitTime);
    }
}

void printAllPatients(struct pQueue *priorityQueue)
{
    struct Node *current = priorityQueue->front;

    while (current != NULL)
    {
        printf("%s %d %s\n", current->patient.name, current->patient.priority, current->patient.admitTime);
        current = current->next;
    }
}

void freePriorityQueue(struct pQueue *priorityQueue)
{
    struct Node *current = priorityQueue->front;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(priorityQueue);
}

int main()
{
    char option;
    char name[1001];
    int priority;
    char admitTime[1001];

    struct pQueue *priorityQueue = initializePriorityQueue();

    do
    {
        scanf(" %c", &option);

        switch (option)
        {
        case 'a':
            scanf(" %s %d %s", name, &priority, admitTime);
            admitPatient(priorityQueue, name, priority, admitTime);
            break;

        case 't':
            treatNextPatient(priorityQueue);
            break;

        case 'c':
            checkNextPatient(priorityQueue);
            break;

        case 'd':
            scanf(" %s %d %s", name, &priority, admitTime);
            dischargePatient(priorityQueue, name, admitTime);
            break;

        case 'u':
            scanf(" %s %s %d", name, admitTime, &priority);
            updateConditionSeverity(priorityQueue, name, admitTime, priority);
            break;

        case 'p':
            printAllPatients(priorityQueue);
            break;

        case 'e':
            break;

        default:
            break;
        }

    } while (option != 'e');

    freePriorityQueue(priorityQueue);

    return 0;
}
