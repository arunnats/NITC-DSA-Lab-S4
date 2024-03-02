#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for patient details
struct Patient
{
    char name[50];
    int priority;
    char admitTime[10];
};

// Define a node structure for the priority queue
struct Node
{
    struct Patient patient;
    struct Node *next;
};

// Define the priority queue structure
struct PriorityQueue
{
    struct Node *front;
};

// Function to create a new node
struct Node *createNode(struct Patient patient)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->patient = patient;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty priority queue
struct PriorityQueue *initializePriorityQueue()
{
    struct PriorityQueue *pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Function to add a new patient to the priority queue
void admitPatient(struct PriorityQueue *pq, struct Patient patient)
{
    struct Node *newNode = createNode(patient);

    if (pq->front == NULL || patient.priority > pq->front->patient.priority ||
        (patient.priority == pq->front->patient.priority &&
         strcmp(patient.admitTime, pq->front->patient.admitTime) < 0))
    {
        newNode->next = pq->front;
        pq->front = newNode;
    }
    else
    {
        struct Node *current = pq->front;
        while (current->next != NULL &&
               (patient.priority < current->next->patient.priority ||
                (patient.priority == current->next->patient.priority &&
                 strcmp(patient.admitTime, current->next->patient.admitTime) >= 0)))
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to treat the next patient with high severity
void treatNextPatient(struct PriorityQueue *pq)
{
    if (pq->front != NULL)
    {
        struct Node *temp = pq->front;
        pq->front = pq->front->next;
        printf("%s %d %s\n", temp->patient.name, temp->patient.priority, temp->patient.admitTime);
        free(temp);
    }
    else
    {
        printf("No patients in the queue.\n");
    }
}

// Function to check the details of the next patient without removing them from the priority queue
void checkNextPatient(struct PriorityQueue *pq)
{
    if (pq->front != NULL)
    {
        printf("%s %d %s\n", pq->front->patient.name, pq->front->patient.priority,
               pq->front->patient.admitTime);
    }
    else
    {
        printf("No patients in the queue.\n");
    }
}

// Function to discharge a specific patient from the priority queue
void dischargePatient(struct PriorityQueue *pq, char name[50], char admitTime[10])
{
    if (pq->front == NULL)
    {
        printf("No patients in the queue.\n");
        return;
    }

    struct Node *current = pq->front;
    struct Node *prev = NULL;

    while (current != NULL &&
           (strcmp(current->patient.name, name) != 0 || strcmp(current->patient.admitTime, admitTime) != 0))
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Patient not found in the queue.\n");
    }
    else
    {
        if (prev == NULL)
        {
            pq->front = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        free(current);
        printf("Patient %s %s discharged.\n", name, admitTime);
    }
}

// Function to update the condition severity of a specific patient in the priority queue
void updateConditionSeverity(struct PriorityQueue *pq, char name[50], char admitTime[10], int newPriority)
{
    if (pq->front == NULL)
    {
        printf("No patients in the queue.\n");
        return;
    }

    struct Node *current = pq->front;

    while (current != NULL &&
           (strcmp(current->patient.name, name) != 0 || strcmp(current->patient.admitTime, admitTime) != 0))
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Patient not found in the queue.\n");
    }
    else
    {
        current->patient.priority = newPriority;
        printf("Condition severity updated for %s %s.\n", name, admitTime);
    }
}

// Function to print the details of all patients in priority order
void printAllPatients(struct PriorityQueue *pq)
{
    struct Node *current = pq->front;

    while (current != NULL)
    {
        printf("%s %d %s\n", current->patient.name, current->patient.priority, current->patient.admitTime);
        current = current->next;
    }
}

// Function to free the memory allocated for the priority queue
void freePriorityQueue(struct PriorityQueue *pq)
{
    struct Node *current = pq->front;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(pq);
}

// Function to handle menu-driven operations
void mainMenu(struct PriorityQueue *pq)
{
    char option;
    do
    {
        printf("Enter option (a, t, c, d, u, p, e): ");
        scanf(" %c", &option);

        switch (option)
        {
        case 'a':
        {
            struct Patient newPatient;
            printf("Enter patient name, priority, and admit time: ");
            scanf("%s %d %s", newPatient.name, &newPatient.priority, newPatient.admitTime);
            admitPatient(pq, newPatient);
            break;
        }
        case 't':
            treatNextPatient(pq);
            break;
        case 'c':
            checkNextPatient(pq);
            break;
        case 'd':
        {
            char name[50], admitTime[10];
            printf("Enter patient name and admit time: ");
            scanf("%s %s", name, admitTime);
            dischargePatient(pq, name, admitTime);
            break;
        }
        case 'u':
        {
            char name[50], admitTime[10];
            int newPriority;
            printf("Enter patient name, admit time, and new priority: ");
            scanf("%s %s %d", name, admitTime, &newPriority);
            updateConditionSeverity(pq, name, admitTime, newPriority);
            break;
        }
        case 'p':
            printAllPatients(pq);
            break;
        case 'e':
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 'e');
}

int main()
{
    struct PriorityQueue *pq = initializePriorityQueue();
    mainMenu(pq);
    freePriorityQueue(pq);

    return 0;
}
