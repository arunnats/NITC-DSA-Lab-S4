#include <stdio.h>

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return (i * 2) + 2;
}

int parent(int i)
{
    return (i - 1) / 2;
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

    if (l < heapSize && arr[l] > arr[max])
        max = l;

    if (r < heapSize && arr[r] > arr[max])
        max = r;

    if (max != i)
        swap(&arr[i], &arr[max]);
}

void buildHeap(int arr[], int heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        maxHeapify(arr, heapSize, i);
}

void heapSort(int arr[], int heapSize)
{
    buildHeap(arr, heapSize);

    for (int i = heapSize - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        maxHeapify(arr, i, 0);
    }
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    printf("Enter %d elements: ", N);

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    heapSort(arr, N);

    printf("\nSorted Array: ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);

    return 0;
}
