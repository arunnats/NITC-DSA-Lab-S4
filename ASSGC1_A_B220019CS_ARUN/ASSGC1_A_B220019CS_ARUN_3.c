#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    char name[100];
    int priority;
    char admitTime[100];
};

struct pQueue
{
    struct Patient *patients;
    int size;
    int capacity;
};

struct pQueue *initializepQueue(int capacity)
{
    struct pQueue *priorityQueue = (struct pQueue *)malloc(sizeof(struct pQueue));
    priorityQueue->patients = (struct Patient *)malloc(sizeof(struct Patient) * (capacity + 1));
    priorityQueue->size = 0;
    priorityQueue->capacity = capacity;
    return priorityQueue;
}

void swap(struct Patient *a, struct Patient *b)
{
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

int comparePatients(struct Patient *a, struct Patient *b)
{
    if (a->priority > b->priority)
        return 1;
    else if (a->priority < b->priority)
        return -1;
    else
    {
        int timeComparison = strcmp(a->admitTime, b->admitTime);
        return timeComparison;
    }
}

void heapifyUp(struct pQueue *priorityQueue, int index)
{
    while (index > 1)
    {
        if (comparePatients(&priorityQueue->patients[index], &priorityQueue->patients[index / 2]) > 0)
        {
            swap(&priorityQueue->patients[index], &priorityQueue->patients[index / 2]);
            index /= 2;
        }
        else
        {
            break;
        }
    }
}

void heapifyDown(struct pQueue *priorityQueue, int index)
{
    while (2 * index <= priorityQueue->size)
    {
        int maxChild = 2 * index;

        if (2 * index + 1 <= priorityQueue->size &&
            comparePatients(&priorityQueue->patients[2 * index], &priorityQueue->patients[2 * index + 1]) < 0)
        {
            maxChild = 2 * index + 1;
        }

        if (comparePatients(&priorityQueue->patients[index], &priorityQueue->patients[maxChild]) < 0)
        {
            swap(&priorityQueue->patients[index], &priorityQueue->patients[maxChild]);
            index = maxChild;
        }
        else
        {
            break;
        }
    }
}

void insertHeap(struct pQueue *priorityQueue, struct Patient newPatient)
{
    priorityQueue->size++;
    int index = priorityQueue->size;
    priorityQueue->patients[index] = newPatient;
    heapifyUp(priorityQueue, index);
}

void removeHeap(struct pQueue *priorityQueue, int index)
{
    swap(&priorityQueue->patients[index], &priorityQueue->patients[priorityQueue->size]);
    priorityQueue->size--;
    heapifyDown(priorityQueue, index);
}
