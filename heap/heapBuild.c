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

void print(int arr[], int heapSize);
{
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n", );
}

int main()
{
    int arr[10001];
    int heapSize = 0;

    char choice;
    int key, newKey;

    do
    {
        scanf(" %c", &choice);

        if (choice == 'i')
        {
            scanf(" %d", &key);
            heapSize = insertHeap(arr, heapSize, key);
        }
        else if (choice == 'm')
        {
            int min = findMin(arr);
            printf("Minimum is %d", min);
        }
        else if (choice == 'e')
        {
            int min = extractMin(arr);
            printf("Minimum is %d \n", min);
        }
        else if (choice == 'u')
        {
            scanf(" %d %d", &key, &newKey);
            updatePriority(arr, heapSize, key, newKey);
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