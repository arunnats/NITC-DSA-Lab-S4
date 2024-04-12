#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int array[MAX_SIZE];
    int front, rear;
} Queue;

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = -1;
    return queue;
}

int isEmpty(Queue *queue)
{
    return queue->front == -1;
}

int isFull(Queue *queue)
{
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void enqueue(Queue *queue, int data)
{
    if (isFull(queue))
    {
        printf("Queue overflow!\n");
        return;
    }
    if (isEmpty(queue))
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }
    queue->array[queue->rear] = data;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underflow!\n");
        return -1;
    }
    int data = queue->array[queue->front];
    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
    return data;
}

int front(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->array[queue->front];
}

void display(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    int i = queue->front;
    do
    {
        printf("%d ", queue->array[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (queue->rear + 1) % MAX_SIZE);
    printf("\n");
}

int main()
{
    Queue *queue = createQueue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    display(queue);

    printf("Dequeued element: %d\n", dequeue(queue));
    printf("Front element: %d\n", front(queue));

    display(queue);

    return 0;
}
