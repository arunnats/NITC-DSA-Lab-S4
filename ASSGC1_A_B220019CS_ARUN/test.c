#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a patient
typedef struct
{
    char name[100];
    int priority;
    char admitTime[100];
} Patient;

// Structure to represent a node in the max heap
typedef struct
{
    Patient *patient;
} Node;

// Structure to represent the priority queue
typedef struct
{
    Node **array;
    int size;
} PriorityQueue;

// Function to swap two nodes in the heap
void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i
void maxHeapify(PriorityQueue *pq, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->array[left]->patient->priority > pq->array[largest]->patient->priority)
        largest = left;

    if (right < pq->size && pq->array[right]->patient->priority > pq->array[largest]->patient->priority)
        largest = right;

    if (largest != i)
    {
        swap(&pq->array[i], &pq->array[largest]);
        maxHeapify(pq, largest);
    }
}

// Function to build a max heap
PriorityQueue *buildMaxHeap()
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->array = NULL;
    pq->size = 0;
    return pq;
}

// Function to insert a new patient into the priority queue
void insertPatient(PriorityQueue *pq, Patient *patient)
{
    // Increase the size of the heap
    pq->size++;
    pq->array = (Node **)realloc(pq->array, pq->size * sizeof(Node *));

    // Create a new node and insert it at the end
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->patient = patient;
    pq->array[pq->size - 1] = newNode;

    // Heapify the heap
    for (int i = pq->size / 2 - 1; i >= 0; i--)
    {
        maxHeapify(pq, i);
    }
}

// Function to treat the next patient with the highest priority
void treatNextPatient(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the ER.\n");
        return;
    }

    // Treat the patient with the highest priority
    printf("%s %d %s\n", pq->array[0]->patient->name, pq->array[0]->patient->priority, pq->array[0]->patient->admitTime);

    // Swap the root (highest priority patient) with the last node
    swap(&pq->array[0], &pq->array[pq->size - 1]);

    // Decrease the size of the heap
    pq->size--;

    // Heapify the heap
    maxHeapify(pq, 0);
}

// Function to check the details of the next patient without removing them
void checkNextPatient(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the ER.\n");
        return;
    }

    // Print the details of the patient with the highest priority
    printf("%s %d %s\n", pq->array[0]->patient->name, pq->array[0]->patient->priority, pq->array[0]->patient->admitTime);
}

// Function to discharge a specific patient from the ER
void dischargePatient(PriorityQueue *pq, char *name, char *admitTime)
{
    int i;
    for (i = 0; i < pq->size; i++)
    {
        if (strcmp(pq->array[i]->patient->name, name) == 0 && strcmp(pq->array[i]->patient->admitTime, admitTime) == 0)
        {
            break;
        }
    }

    if (i == pq->size)
    {
        printf("Patient not found in the ER.\n");
        return;
    }

    // Swap the patient to be discharged with the last node
    swap(&pq->array[i], &pq->array[pq->size - 1]);

    // Decrease the size of the heap
    pq->size--;

    // Heapify the heap
    for (int j = pq->size / 2 - 1; j >= 0; j--)
    {
        maxHeapify(pq, j);
    }

    printf("Patient %s discharged.\n", name);
}

// Function to update the condition severity of a specific patient
void updateConditionSeverity(PriorityQueue *pq, char *name, char *admitTime, int newPriority)
{
    int i;
    for (i = 0; i < pq->size; i++)
    {
        if (strcmp(pq->array[i]->patient->name, name) == 0 && strcmp(pq->array[i]->patient->admitTime, admitTime) == 0)
        {
            break;
        }
    }

    if (i == pq->size)
    {
        printf("Patient not found in the ER.\n");
        return;
    }

    // Update the priority of the patient
    pq->array[i]->patient->priority = newPriority;

    // Heapify the heap
    for (int j = pq->size / 2 - 1; j >= 0; j--)
    {
        maxHeapify(pq, j);
    }

    printf("Condition severity updated for patient %s.\n", name);
}

// Function to print details of all patients in priority order
void printAllPatients(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the ER.\n");
        return;
    }

    for (int i = 0; i < pq->size; i++)
    {
        printf("%s %d %s\n", pq->array[i]->patient->name, pq->array[i]->patient->priority, pq->array[i]->patient->admitTime);
    }
}

// Function to free the memory allocated for the priority queue
void freePriorityQueue(PriorityQueue *pq)
{
    for (int i = 0; i < pq->size; i++)
    {
        free(pq->array[i]->patient);
        free(pq->array[i]);
    }
    free(pq->array);
    free(pq);
}

int main()
{
    char option;
    PriorityQueue *priorityQueue = buildMaxHeap();

    do
    {
        scanf(" %c", &option);

        switch (option)
        {
        case 'a':
        {
            char name[100];
            int priority;
            char admitTime[100];
            scanf("%s %d %s", name, &priority, admitTime);

            Patient *newPatient = (Patient *)malloc(sizeof(Patient));
            strcpy(newPatient->name, name);
            newPatient->priority = priority;
            strcpy(newPatient->admitTime, admitTime);

            insertPatient(priorityQueue, newPatient);
            break;
        }
        case 't':
            treatNextPatient(priorityQueue);
            break;
        case 'c':
            checkNextPatient(priorityQueue);
            break;
        case 'd':
        {
            char name[100];
            char admitTime[100];
            scanf("%s %s", name, admitTime);
            dischargePatient(priorityQueue, name, admitTime);
            break;
        }
        case 'u':
        {
            char name[100];
            char admitTime[100];
            int newPriority;
            scanf("%s %s %d", name, admitTime, &newPriority);
            updateConditionSeverity(priorityQueue, name, admitTime, newPriority);
            break;
        }
        case 'p':
            printAllPatients(priorityQueue);
            break;
        case 'e':
            break;
        default:
            printf("Invalid option. Try again.\n");
        }

    } while (option != 'e');

    freePriorityQueue(priorityQueue);

    return 0;
}
