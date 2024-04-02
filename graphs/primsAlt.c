#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge
{
    int source;
    int destination;
    int weight;
};

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

struct PriorityQueue
{
    struct HeapNode **heapNodes;
    int size;
    int capacity;
};

struct HeapNode
{
    int vertex;
    int weight;
};

struct HeapNode *createHeapNode(int vertex, int weight)
{
    struct HeapNode *newNode = (struct HeapNode *)malloc(sizeof(struct HeapNode));
    newNode->vertex = vertex;
    newNode->weight = weight;
    return newNode;
}

struct PriorityQueue *createPriorityQueue(int capacity)
{
    struct PriorityQueue *pQueue = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pQueue->heapNodes = (struct HeapNode **)malloc(capacity * sizeof(struct HeapNode *));
    pQueue->size = 0;
    pQueue->capacity = capacity;
    return pQueue;
}

void freePriorityQueue(struct PriorityQueue *pQueue)
{
    for (int i = 0; i < pQueue->size; ++i)
    {
        free(pQueue->heapNodes[i]);
    }
    free(pQueue->heapNodes);
    free(pQueue);
}

void swap(struct HeapNode **a, struct HeapNode **b)
{
    struct HeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct HeapNode **queue, int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && queue[left]->weight < queue[smallest]->weight)
    {
        smallest = left;
    }

    if (right < size && queue[right]->weight < queue[smallest]->weight)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&queue[i], &queue[smallest]);
        heapify(queue, size, smallest);
    }
}

struct HeapNode *extractMin(struct PriorityQueue *pQueue)
{
    if (pQueue->size == 0)
    {
        return NULL;
    }

    struct HeapNode *minNode = pQueue->heapNodes[0];
    pQueue->heapNodes[0] = pQueue->heapNodes[pQueue->size - 1];
    (pQueue->size)--;
    heapify(pQueue->heapNodes, pQueue->size, 0);

    return minNode;
}

void primsMST(struct Graph *graph, int startVertex)
{
    int numVertices = graph->numVertices;
    int *parent = (int *)malloc(numVertices * sizeof(int));
    int *key = (int *)malloc(numVertices * sizeof(int));
    int *inMST = (int *)malloc(numVertices * sizeof(int));

    struct PriorityQueue *pQueue = createPriorityQueue(numVertices);

    for (int v = 0; v < numVertices; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        inMST[v] = 0;
    }

    key[startVertex] = 0;
    struct HeapNode *startNode = createHeapNode(startVertex, key[startVertex]);
    pQueue->heapNodes[pQueue->size++] = startNode;

    while (pQueue->size > 0)
    {
        struct HeapNode *minNode = extractMin(pQueue);
        int u = minNode->vertex;
        inMST[u] = 1;

        for (int v = 0; v < numVertices; ++v)
        {
            if (graph->adjMatrix[u][v] && !inMST[v] && graph->adjMatrix[u][v] < key[v])
            {
                key[v] = graph->adjMatrix[u][v];
                parent[v] = u;
                struct HeapNode *newNode = createHeapNode(v, key[v]);
                pQueue->heapNodes[pQueue->size++] = newNode;
            }
        }
    }

    // Print the MST edges
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < numVertices; ++i)
    {
        printf("Edge: %d - %d, Weight: %d\n", parent[i], i, graph->adjMatrix[i][parent[i]]);
    }

    free(parent);
    free(key);
    free(inMST);
    freePriorityQueue(pQueue);
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
    graph->adjMatrix[dest][src] = weight; // For undirected graph
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
            {
                printf("x ");
            }
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
            {
                addEdge(graph, i, j, weight);
            }
        }
    }

    printGraph(graph);

    int startVertex;
    scanf(" %d", &startVertex);
    primsMST(graph, startVertex);

    return 0;
}
