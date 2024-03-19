#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000
#define UNVISITED -1

struct Node
{
    int destination;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    int V;
    struct List *array;
};

struct Node *createNode(int destination)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->destination = destination;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct List *)malloc(V * sizeof(struct List));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph *graph, int source, int destination)
{
    struct Node *newNode = createNode(destination);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;

    newNode = createNode(source);
    newNode->next = graph->array[destination].head;
    graph->array[destination].head = newNode;
}

void DFSUtil(struct Graph *graph, int v, int *visited, int *componentSize)
{
    visited[v] = 1;
    componentSize[v]++;

    struct Node *temp = graph->array[v].head;
    while (temp)
    {
        int adj = temp->destination;
        if (!visited[adj])
            DFSUtil(graph, adj, visited, componentSize);
        temp = temp->next;
    }
}

int noOfConnectedComponents(struct Graph *graph)
{
    int *visited = (int *)malloc(graph->V * sizeof(int));
    int *componentSize = (int *)calloc(graph->V, sizeof(int));
    int count = 0;

    for (int i = 0; i < graph->V; ++i)
    {
        visited[i] = 0;
        componentSize[i] = 0;
    }

    for (int i = 0; i < graph->V; ++i)
    {
        if (!visited[i])
        {
            count++;
            DFSUtil(graph, i, visited, componentSize);
        }
    }

    free(visited);
    free(componentSize);

    return count;
}

void sizeOfComponents(struct Graph *graph)
{
    int *visited = (int *)malloc(graph->V * sizeof(int));
    int *componentSize = (int *)calloc(graph->V, sizeof(int));

    for (int i = 0; i < graph->V; ++i)
    {
        visited[i] = 0;
        componentSize[i] = 0;
    }

    for (int i = 0; i < graph->V; ++i)
    {
        if (!visited[i])
        {
            DFSUtil(graph, i, visited, componentSize);
        }
    }

    // Print the sizes of connected components in increasing order
    printf("Sizes of connected components in the graph:\n");
    for (int i = 0; i < graph->V; ++i)
    {
        if (componentSize[i] > 0)
        {
            printf("Component %d: %d\n", i + 1, componentSize[i]);
        }
    }

    free(visited);
    free(componentSize);
}

int main()
{
    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m);

    for (int i = 0; i < m; ++i)
    {
        int label, adj;
        scanf("%d", &label);
        while (scanf("%d", &adj) == 1 && adj != label)
        {
            addEdge(graph, label - 1, adj - 1);
        }
    }

    int connectedComponents = noOfConnectedComponents(graph);
    printf("Total number of connected components in the graph: %d\n", connectedComponents);

    sizeOfComponents(graph);

    return 0;
}
