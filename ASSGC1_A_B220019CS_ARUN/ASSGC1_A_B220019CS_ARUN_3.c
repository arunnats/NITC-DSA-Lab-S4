#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    char name[100];
    int priority;
    char admitTime[100];
};

struct PQueue
{
    struct Patient *patients;
    int size;
    int capacity;
};

void swap(struct Patient *a, struct Patient *b)
{
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}
