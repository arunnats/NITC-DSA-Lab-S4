#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

struct PriorityQueueNode
{
    int vertex;
    int priority;
};

struct PriorityQueue
{
    struct PriorityQueueNode *nodes;
    int capacity;
    int size;
};

struct PriorityQueue *initPriorityQueue(int capacity)
{
    struct PriorityQueue *pQueue = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pQueue->nodes = (struct PriorityQueueNode *)malloc(capacity * sizeof(struct PriorityQueueNode));
    pQueue->capacity = capacity;
    pQueue->size = 0;
    return pQueue;
}

void enqueue(struct PriorityQueue *pQueue, int vertex, int priority)
{
    if (pQueue->size >= pQueue->capacity)
    {
        printf("Priority queue overflow\n");
        return;
    }
    pQueue->nodes[pQueue->size].vertex = vertex;
    pQueue->nodes[pQueue->size].priority = priority;
    pQueue->size++;
}

struct PriorityQueueNode dequeue(struct PriorityQueue *pQueue)
{
    if (pQueue->size == 0)
    {
        printf("Priority queue underflow\n");
        exit(1);
    }
    int minIndex = 0;
    for (int i = 1; i < pQueue->size; ++i)
    {
        if (pQueue->nodes[i].priority < pQueue->nodes[minIndex].priority)
        {
            minIndex = i;
        }
    }
    struct PriorityQueueNode minNode = pQueue->nodes[minIndex];
    for (int i = minIndex; i < pQueue->size - 1; ++i)
    {
        pQueue->nodes[i] = pQueue->nodes[i + 1];
    }
    pQueue->size--;
    return minNode;
}

int isEmpty(struct PriorityQueue *pQueue)
{
    return pQueue->size == 0;
}

struct Graph *createGraph(int numVertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; ++i)
    {
        graph->adjMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; ++j)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
}

void primsMST(struct Graph *graph, int startVertice)
{
    int *visited = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = 0;
    }

    int *unvisited = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        unvisited[i] = 1;
    }

    int *parent = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        parent[i] = -1;
    }

    struct PriorityQueue *pQueue = initPriorityQueue(graph->numVertices);
    int totalWeight = 0;

    enqueue(pQueue, startVertice, 0);
    visited[startVertice] = 1;
    unvisited[startVertice] = 0;

    while (!isEmpty(pQueue))
    {
        struct PriorityQueueNode minNode = dequeue(pQueue);
        int minVertex = minNode.vertex;
        int minPriority = minNode.priority;

        if (parent[minVertex] != -1)
        {
            printf("Edge: %d-%d, Weight: %d\n", parent[minVertex], minVertex, minPriority);
            totalWeight += minPriority;
        }

        visited[minVertex] = 1;

        for (int i = 0; i < graph->numVertices; ++i)
        {
            if (graph->adjMatrix[minVertex][i] != 0 && !visited[i])
            {
                if (graph->adjMatrix[minVertex][i] < pQueue->nodes[i].priority)
                {
                    pQueue->nodes[i].priority = graph->adjMatrix[minVertex][i];
                    parent[i] = minVertex; // Update parent
                }
                enqueue(pQueue, i, graph->adjMatrix[minVertex][i]);
            }
        }
    }

    printf("Total weight of MST: %d\n", totalWeight);
}

void printGraph(struct Graph *graph)
{
    printf("Adjacency matrix \n");

    for (int i = 0; i < graph->numVertices; ++i)
    {

        for (int j = 0; j < graph->numVertices; ++j)
        {
            if (graph->adjMatrix[i][j] != 0)
            {
                printf("%d ", graph->adjMatrix[i][j]);
            }
            else
                printf("x ");
        }

        printf("\n");
    }
}

int main()
{
    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int weight;
            scanf("%d", &weight);
            if (weight)
                addEdge(graph, i, j, weight);
        }
    }

    printGraph(graph);

    int startVertex;
    scanf(" %d", &startVertex);
    primsMST(graph, startVertex);

    return 0;
}