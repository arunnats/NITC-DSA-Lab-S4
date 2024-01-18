#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient
{
    char name[50];
    int priority;
    char admitTime[10];
} Patient;

typedef struct PriorityQueue
{
    int size;
    int capacity;
    Patient *array;
} PriorityQueue;

PriorityQueue *createQueue(int capacity)
{
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->array = (Patient *)malloc(queue->capacity * sizeof(Patient));
    return queue;
}

void swap(Patient *a, Patient *b)
{
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue *queue, int idx)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size && queue->array[left].priority > queue->array[largest].priority)
        largest = left;

    if (right < queue->size && queue->array[right].priority > queue->array[largest].priority)
        largest = right;

    if (largest != idx)
    {
        swap(&queue->array[largest], &queue->array[idx]);
        heapify(queue, largest);
    }
}

void admitPatient(PriorityQueue *queue, char *name, int priority, char *admitTime)
{
    if (queue->size == queue->capacity)
    {
        printf("Queue is full\n");
        return;
    }

    Patient newPatient;
    strcpy(newPatient.name, name);
    newPatient.priority = priority;
    strcpy(newPatient.admitTime, admitTime);

    queue->size++;
    int i = queue->size - 1;
    queue->array[i] = newPatient;

    while (i != 0 && queue->array[(i - 1) / 2].priority < queue->array[i].priority)
    {
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    heapify(queue, 0);
}

Patient treatNextPatient(PriorityQueue *queue)
{
    if (queue->size <= 0)
    {
        printf("Queue is empty\n");
        Patient patient;
        strcpy(patient.name, "");
        strcpy(patient.admitTime, "");
        patient.priority = -1;
        return patient;
    }

    if (queue->size == 1)
    {
        queue->size--;
        return queue->array[0];
    }

    Patient root = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;
    heapify(queue, 0);

    return root;
}

void printPatientsRecursive(PriorityQueue *queue, int index)
{
    if (index >= queue->size)
        return;

    // Print the current patient
    printf("%s %d %s\n", queue->array[index].name, queue->array[index].priority, queue->array[index].admitTime);

    // Recursively print left and right children
    printPatientsRecursive(queue, 2 * index + 2);
    printPatientsRecursive(queue, 2 * index + 1);
}

void printAllPatients(PriorityQueue *queue)
{
    // Start the recursive printing from the root (highest priority patient)
    printPatientsRecursive(queue, 0);
}

int main()
{
    char option;
    char name[1001];
    int priority;
    char admitTime[1001];

    PriorityQueue *priorityQueue = createQueue(1001);

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

        case 'p':
            printAllPatients(priorityQueue);
            break;

        case 'e':
            break;

        default:
            break;
        }

    } while (option != 'e');

    free(priorityQueue->array);
    free(priorityQueue);

    return 0;
}
