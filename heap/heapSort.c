#include <stdio.h>

int left(int i)
{
    return i * 2;
}

int right(int i)
{
    return (i * 2) + 1;
}

int parent(int i)
{
    return i / 2;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void maxHeapify(int arr[], int heapSize, int i)
{
    int l = left(i);
    int r = right(i);

    int max = i;

    if (l < heapSize && arr[i] > arr[l])
        max = arr[l];

    if (r < heapSize && arr[r] > arr[max])
        max = arr[r];

    if (max != i)
        swap(&arr[i], &arr[max]);
}

void buildHeap(int arr[], int heapSize)
{
}

void main()
{
    int N;

    printf("Enter N ");
    scanf("%d", &N);

    printf("Enter %d elements", N);

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
}