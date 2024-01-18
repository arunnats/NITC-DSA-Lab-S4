#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    char name[1001];
    int priority;
    char admitTime[1001];
};

struct pQueue
{
    struct Patient *patients;
    int size;
    int capacity;
};

struct pQueue *initializePriorityQueue(int capacity)
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
        int a_hour, a_minute, b_hour, b_minute;
        sscanf(a->admitTime, "%d:%d", &a_hour, &a_minute);
        sscanf(b->admitTime, "%d:%d", &b_hour, &b_minute);

        if (a_hour > b_hour || (a_hour == b_hour && a_minute > b_minute))
            return 1;
        else if (a_hour < b_hour || (a_hour == b_hour && a_minute < b_minute))
            return -1;
        else
            return 0;
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
    if (priorityQueue->size == 0)
    {
        printf("-1");
        return;
    }
    else
    {
        printf("%s ", priorityQueue->patients[1].name);
        printf("%d ", priorityQueue->patients[1].priority);
        printf("%s\n", priorityQueue->patients[1].admitTime);
        removeHeap(priorityQueue, 1);
    }
}

void checkNextPatient(struct pQueue *priorityQueue)
{
    if (priorityQueue->size == 0)
    {
        printf("-1");
        return;
    }
    else
    {
        printf("%s ", priorityQueue->patients[1].name);
        printf("%d ", priorityQueue->patients[1].priority);
        printf("%s\n", priorityQueue->patients[1].admitTime);
    }
}

void dischargePatient(struct pQueue *priorityQueue, char *name, char *admitTime)
{
    int i;
    for (i = 1; i <= priorityQueue->size; i++)
    {
        if (strcmp(priorityQueue->patients[i].name, name) == 0 && strcmp(priorityQueue->patients[i].admitTime, admitTime) == 0)
        {
            removeHeap(priorityQueue, i);
            return;
        }
    }
    printf("-1\n");
    return;
}

void updateConditionSeverity(struct pQueue *priorityQueue, char *name, char *admitTime, int newPriority)
{
    int i;
    for (i = 1; i <= priorityQueue->size; i++)
    {
        if (strcmp(priorityQueue->patients[i].name, name) == 0 && strcmp(priorityQueue->patients[i].admitTime, admitTime) == 0)
        {
            removeHeap(priorityQueue, i);

            struct Patient updatedPatient;
            strcpy(updatedPatient.name, name);
            updatedPatient.priority = newPriority;
            strcpy(updatedPatient.admitTime, admitTime);

            insertHeap(priorityQueue, updatedPatient);

            return;
        }
    }
    printf("-1\n");
    return;
}

void printAllPatients(struct pQueue *priorityQueue)
{
    int i;
    for (i = 1; i <= priorityQueue->size; i++)
    {
        printf("%s ", priorityQueue->patients[i].name);
        printf("%d ", priorityQueue->patients[i].priority);
        printf("%s\n", priorityQueue->patients[i].admitTime);
    }
    return;
}

int main()
{
    char option;
    char name[1001];
    int priority;
    char admitTime[1001];

    struct pQueue *priorityQueue = initializePriorityQueue(1001);

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

    free(priorityQueue->patients);
    free(priorityQueue);

    return 1;
}