#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    char name[50];
    int priority;
    char admitTime[10];
};

struct Node
{
    struct Patient patient;
};

void swap(struct Node *priorityQueue, int i, int j)
{
    struct Node temp = priorityQueue[i];
    priorityQueue[i] = priorityQueue[j];
    priorityQueue[j] = temp;
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

void heapify(struct Node *priorityQueue, int size, int index)
{
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild < size && comparePatients(&priorityQueue[leftChild].patient, &priorityQueue[largest].patient) > 0)
    {
        largest = leftChild;
    }

    if (rightChild < size && comparePatients(&priorityQueue[rightChild].patient, &priorityQueue[largest].patient) > 0)
    {
        largest = rightChild;
    }

    if (largest != index)
    {
        swap(priorityQueue, index, largest);
        heapify(priorityQueue, size, largest);
    }
}

void heapifyUp(struct Node *priorityQueue, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (comparePatients(&priorityQueue[index].patient, &priorityQueue[parent].patient) > 0)
        {
            swap(priorityQueue, index, parent);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void admitPatient(struct Node *priorityQueue, int *index, char name[], int priority, char admitTime[])
{
    struct Patient newPatient;
    strcpy(newPatient.name, name);
    newPatient.priority = priority;
    strcpy(newPatient.admitTime, admitTime);

    struct Node newNode;
    newNode.patient = newPatient;

    priorityQueue[*index] = newNode;
    int current = *index;
    (*index)++;

    heapifyUp(priorityQueue, current);
}

void treatNextPatient(struct Node *priorityQueue, int *index)
{
    if (*index == 0)
    {
        printf("-1\n");
        return;
    }

    printf("%s %d %s\n", priorityQueue[0].patient.name, priorityQueue[0].patient.priority, priorityQueue[0].patient.admitTime);

    swap(priorityQueue, 0, (*index) - 1);
    (*index)--;
}

void checkNextPatient(struct Node *priorityQueue, int *index)
{
    if (*index == 0)
    {
        printf("-1\n");
        return;
    }

    printf("%s %d %s\n", priorityQueue[0].patient.name, priorityQueue[0].patient.priority, priorityQueue[0].patient.admitTime);
}

void dischargePatient(struct Node *priorityQueue, int *index, char name[], char admitTime[])
{
    int i;
    for (i = 0; i < *index; i++)
    {
        if (strcmp(priorityQueue[i].patient.name, name) == 0 && strcmp(priorityQueue[i].patient.admitTime, admitTime) == 0)
        {
            break;
        }
    }

    if (i == *index)
    {
        printf("P-1\n");
        return;
    }

    swap(priorityQueue, i, (*index) - 1);
    (*index)--;

    heapify(priorityQueue, *index, i);
}

void updateConditionSeverity(struct Node *priorityQueue, int *index, char name[], char admitTime[], int newPriority)
{
    int i;
    for (i = 0; i < *index; i++)
    {
        if (strcmp(priorityQueue[i].patient.name, name) == 0 && strcmp(priorityQueue[i].patient.admitTime, admitTime) == 0)
        {
            break;
        }
    }

    if (i == *index)
    {
        printf("-1\n");
        return;
    }

    priorityQueue[i].patient.priority = newPriority;

    while (i > 0 && comparePatients(&priorityQueue[i].patient, &priorityQueue[(i - 1) / 2].patient) > 0)
    {
        swap(priorityQueue, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }

    heapify(priorityQueue, *index, i);
}

void printAllPatients(struct Node *priorityQueue, int *index)
{
    for (int i = 0; i < *index; i++)
    {
        printf("%s %d %s\n", priorityQueue[i].patient.name, priorityQueue[i].patient.priority, priorityQueue[i].patient.admitTime);
    }
}

int main()
{
    char operation;
    char name[50];
    int priority;
    char admitTime[10];
    struct Node priorityQueue[1000];
    int index = 0;

    while (1)
    {
        scanf(" %c", &operation);

        switch (operation)
        {
        case 'a':
            scanf("%s %d %s", name, &priority, admitTime);
            admitPatient(priorityQueue, &index, name, priority, admitTime);
            break;

        case 't':
            treatNextPatient(priorityQueue, &index);
            break;

        case 'c':
            checkNextPatient(priorityQueue, &index);
            break;

        case 'd':
            scanf("%s %s", name, admitTime);
            dischargePatient(priorityQueue, &index, name, admitTime);
            break;

        case 'u':
            scanf("%s %s %d", name, admitTime, &priority);
            updateConditionSeverity(priorityQueue, &index, name, admitTime, priority);
            break;

        case 'p':
            printAllPatients(priorityQueue, &index);
            break;

        case 'e':
            exit(0);
        }
    }

    return 1;
}
