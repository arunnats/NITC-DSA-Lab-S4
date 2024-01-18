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

void enqueue(PriorityQueue *queue, Patient patient)
{
    if (queue->size == queue->capacity)
    {
        printf("Queue is full\n");
        return;
    }

    queue->size++;
    int i = queue->size - 1;
    queue->array[i] = patient;

    while (i != 0 && queue->array[(i - 1) / 2].priority < queue->array[i].priority)
    {
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Patient dequeue(PriorityQueue *queue)
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

int main()
{
    PriorityQueue *queue = createQueue(100);

    Patient patient1;
    strcpy(patient1.name, "John");
    strcpy(patient1.admitTime, "10:30");
    patient1.priority = 5;
    enqueue(queue, patient1);

    Patient patient2;
    strcpy(patient2.name, "Jane");
    strcpy(patient2.admitTime, "11:00");
    patient2.priority = 10;
    enqueue(queue, patient2);

    Patient patient3;
    strcpy(patient3.name, "Bob");
    strcpy(patient3.admitTime, "10:45");
    patient3.priority = 7;
    enqueue(queue, patient3);

    Patient nextPatient = dequeue(queue);
    printf("Next patient: %s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);
    nextPatient = dequeue(queue);
    printf("Next patient: %s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);
    nextPatient = dequeue(queue);
    printf("Next patient: %s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);

    return 0;
}
