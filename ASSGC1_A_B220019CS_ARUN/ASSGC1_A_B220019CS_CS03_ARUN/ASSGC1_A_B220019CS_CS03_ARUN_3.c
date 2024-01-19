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

int comparePatients(struct Patient *a, struct Patient *b)
{
    if (a->priority > b->priority)
        return 1;
    else if (a->priority < b->priority)
        return -1;
    else
    {
        int a_hour, a_minute, b_hour, b_minute;
        sscanf(a->admitTime, "%d:%d", &a_hour, &a_minute);
        sscanf(b->admitTime, "%d:%d", &b_hour, &b_minute);

        if (a_hour > b_hour || (a_hour == b_hour && a_minute > b_minute))
            return -1;
        else if (a_hour < b_hour || (a_hour == b_hour && a_minute < b_minute))
            return 1;
        else
            return 0;
    }
}

void insertHeap(struct pQueue *priorityQueue, struct Patient newPatient)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->patient = newPatient;
    newNode->next = NULL;

    if (priorityQueue->front == NULL || comparePatients(&newPatient, &(priorityQueue->front->patient)) > 0)
    {
        newNode->next = priorityQueue->front;
        priorityQueue->front = newNode;
    }
    else
    {
        struct Node *current = priorityQueue->front;
        while (current->next != NULL && comparePatients(&newPatient, &(current->next->patient)) <= 0)
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

    while (current != NULL)
    {
        if (strcmp(current->patient.name, name) == 0 && strcmp(current->patient.admitTime, admitTime) == 0)
        {
            if (prev == NULL)
            {
                priorityQueue->front = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            printf("%s %d %s\n", name, current->patient.priority, admitTime);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("-1\n");
}

// void dischargePatient(struct pQueue *priorityQueue, int priority)
// {
//     if (priorityQueue->front == NULL)
//     {
//         printf("-1\n");
//         return;
//     }

//     struct Node *current = priorityQueue->front;
//     struct Node *prev = NULL;

//     while (current != NULL)
//     {
//         if (current->patient.priority == priority)
//         {
//             if (prev == NULL)
//             {
//                 priorityQueue->front = current->next;
//             }
//             else
//             {
//                 prev->next = current->next;
//             }

//             printf("%s %d %s\n", current->patient.name, current->patient.priority, current->patient.admitTime);
//             free(current);
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }

//     printf("-1\n");
// }

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
        if (prev == NULL)
        {
            priorityQueue->front = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        free(current);

        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        strcpy(newNode->patient.name, name);
        newNode->patient.priority = newPriority;
        strcpy(newNode->patient.admitTime, admitTime);
        newNode->next = NULL;

        insertHeap(priorityQueue, newNode->patient);

        printf("%s %d %s\n", name, newPriority, admitTime);
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

            // case 'd':
            //     scanf(" %d", priority);
            //     dischargePatient(priorityQueue, priority);
            // break;

        case 'd':
            scanf(" %s %s", name, admitTime);
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

    return 1;
}
