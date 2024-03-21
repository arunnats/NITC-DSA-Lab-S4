#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct
{
    int front, rear, size;
    int capacity;
    int *array;
} Queue;

typedef struct
{
    int numnodes;
    int **matrix; // 2d array
} Graph;

Queue *createqueue(int n)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = n;
    queue->front = queue->size = 0;
    queue->rear = n - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}

Graph *creategraph(int n)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numnodes = n;
    graph->matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        graph->matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return graph;
}

int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

int isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

void enqueue(Queue *queue, int num)
{
    if (isFull(queue))
    {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = num;
    queue->size += 1;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        return -1;
    }
    int del = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return del;
}

int isTopologicalSort(Graph *graph, int n)
{
    int indegree[n];
    for (int i = 0; i < n; i++)
    {
        indegree[i] = 0;
    }

    // Calculate indegrees
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph->matrix[i][j])
            {
                indegree[j]++;
            }
        }
    }

    Queue *q = createqueue(n);
    int count = 0;

    // Check if they're already zero
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            enqueue(q, i);
        }
    }

    // Process nodes
    while (!isEmpty(q))
    {
        int node = dequeue(q);
        count++;
        for (int v = 0; v < n; v++)
        {
            if (graph->matrix[node][v])
            {
                indegree[v]--;
                if (indegree[v] == 0)
                {
                    enqueue(q, v);
                }
            }
        }
    }

    free(q->array);
    free(q);

    if (count == n)
        return 1;
    else
        return -1;
}

void addEdge(Graph *graph, int u, int v)
{
    graph->matrix[u][v] = 1;
}

void DFS(int u, Graph *graph, int *visited, int *stack, int *stackIndex)
{
    visited[u] = 1;
    for (int i = 0; i < graph->numnodes; i++)
    {
        if (graph->matrix[u][i] && !visited[i])
        {
            DFS(i, graph, visited, stack, stackIndex);
        }
    }
    stack[(*stackIndex)++] = u;
}

void transposeGraph(Graph *graph, Graph *transposedGraph)
{
    for (int u = 0; u < graph->numnodes; u++)
    {
        for (int i = 0; i < graph->numnodes; i++)
        {
            if (graph->matrix[u][i])
            {
                transposedGraph->matrix[i][u] = 1;
            }
        }
    }
}

void DFSUtil(int u, Graph *graph, int *visited)
{
    visited[u] = 1;
    for (int i = 0; i < graph->numnodes; i++)
    {
        if (graph->matrix[u][i] && !visited[i])
        {
            DFSUtil(i, graph, visited);
        }
    }
}

int countSCC(Graph *graph, int n)
{
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    int stack[n];
    int stackIndex = 0;

    // Step 1: Fill stack according to finish times
    for (int u = 0; u < graph->numnodes; u++)
    {
        if (!visited[u])
        {
            DFS(u, graph, visited, stack, &stackIndex);
        }
    }

    // Step 2: Create a transposed graph
    Graph *transposedGraph = creategraph(graph->numnodes);
    transposeGraph(graph, transposedGraph);

    // Step 3: Initialize visited array for second DFS
    for (int u = 0; u < graph->numnodes; u++)
    {
        visited[u] = 0;
    }

    // Step 4: Count SCCs using second DFS
    int count = 0;
    while (stackIndex > 0)
    {
        int u = stack[--stackIndex];
        if (!visited[u])
        {
            DFSUtil(u, transposedGraph, visited);
            count++;
        }
    }

    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    Graph *graph = creategraph(n);
    int num;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &num);
            graph->matrix[i][j] = num;
        }
    }
    char ch;
    while (1)
    {
        scanf(" %c", &ch);
        if (ch == 't')
        {
            printf("%d\n", isTopologicalSort(graph, n));
        }
        else if (ch == 'c')
        {
            printf("%d\n", countSCC(graph, n));
        }
        else if (ch == 'x')
        {
            break;
        }
    }
    return 0;
}