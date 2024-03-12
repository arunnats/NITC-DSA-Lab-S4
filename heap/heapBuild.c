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

void minHeapify(int arr[], int heapSize, int i)
{
    int l = left(i);
    int r = right(i);

    int min = i;

    if (l < heapSize && arr[l] < arr[min])
        min = l;

    if (r < heapSize && arr[r] < arr[min])
        min = r;

    if (min != i)
    {
        swap(&arr[i], &arr[min]);
        minHeapify(arr, heapSize, min);
    }
}

void buildMinHeap(int arr[], int heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        minHeapify(arr, heapSize, i);
}

void print(int arr[], int heapSize)
{
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int insertMinHeap(int arr[], int heapSize, int key)
{
    arr[heapSize] = key;
    heapSize++;
    buildMinHeap(arr, heapSize);

    return heapSize;
}

int findMin(int arr[])
{
    return arr[0];
}

int extractMin(int arr[], int heapSize)
{
    if (heapSize <= 0)
        return -1;

    int min = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;

    minHeapify(arr, heapSize, 0);

    return min;
}

int main()
{
    int arr[10001];
    int heapSize = 0;

    char choice;
    int key;

    do
    {
        scanf(" %c", &choice);

        if (choice == 'i')
        {
            scanf(" %d", &key);
            heapSize = insertMinHeap(arr, heapSize, key);
        }
        else if (choice == 'm')
        {
            int min = findMin(arr);
            printf("Minimum is %d\n", min);
        }
        else if (choice == 'e')
        {
            int min = extractMin(arr, heapSize);
            if (min != -1)
                printf("Minimum is %d\n", min);
            else
                printf("Heap is empty.\n");
        }
        else if (choice == 'p')
        {
            print(arr, heapSize);
        }
        else if (choice == 't')
        {
            break;
        }
    } while (1);

    return 0;
}
