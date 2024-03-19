#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

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
}

void printGraph(struct Graph *graph)
{
    printf("Adjacency List Representation of the Graph:\n");
    for (int v = 0; v < graph->V; ++v)
    {
        printf("Node %d -> ", v + 1); // Adjusted to start from 1
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            printf("%d ", temp->destination + 1); // Adjusted to start from 1
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFSUtil(struct Graph *graph, int v, int *visited, int *componentSize, int componentIndex)
{
    visited[v] = 1;
    componentSize[componentIndex]++;

    struct Node *temp = graph->array[v].head;
    while (temp)
    {
        int adj = temp->destination;
        if (!visited[adj])
            DFSUtil(graph, adj, visited, componentSize, componentIndex);
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
            DFSUtil(graph, i, visited, componentSize, count - 1);
        }
    }

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

    int count = 0;
    for (int i = 0; i < graph->V; ++i)
    {
        if (!visited[i])
        {
            count++;
            DFSUtil(graph, i, visited, componentSize, count - 1);
        }
    }

    printf("Sizes of connected components in the graph:\n");
    for (int i = 0; i < count; ++i)
    {
        printf("Component %d: %d\n", i + 1, componentSize[i]);
    }
}

int main()
{
    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m);

    int label, adj;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label); // Read the label of the node
        while (scanf("%d", &adj) == 1)
        {
            addEdge(graph, label - 1, adj - 1); // Add an edge between label and adj
            char c = getchar();
            if (c == '\n')
                break; // End of line
        }
    }

    printGraph(graph);

    int connectedComponents = noOfConnectedComponents(graph);
    printf("Total number of connected components in the graph: %d\n", connectedComponents);

    sizeOfComponents(graph);

    return 0;
}
