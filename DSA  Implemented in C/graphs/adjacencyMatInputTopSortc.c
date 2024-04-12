#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
        printf("Node %d -> ", v); // Adjusted to start from 0
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            printf("%d ", temp->destination); // Adjusted to start from 0
            temp = temp->next;
        }
        printf("\n");
    }
}

// Utility function for topological sort
void topologicalSortUtil(struct Graph *graph, int v, bool visited[], int stack[], int *index)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    struct Node *temp = graph->array[v].head;
    while (temp)
    {
        int adj = temp->destination;
        if (!visited[adj])
            topologicalSortUtil(graph, adj, visited, stack, index);
        temp = temp->next;
    }

    // Push current vertex to stack which stores result
    stack[(*index)++] = v;
}

// Function to perform topological sort
void topologicalSort(struct Graph *graph)
{
    int stack[MAX_NODES];
    int index = 0;

    // Mark all the vertices as not visited
    bool *visited = (bool *)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;

    // Call the utility function to store topological sort starting from all vertices one by one
    for (int i = 0; i < graph->V; i++)
        if (!visited[i])
            topologicalSortUtil(graph, i, visited, stack, &index);

    // Print the contents of the stack
    printf("Topological Sort: ");
    for (int i = graph->V - 1; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");

    free(visited);
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
            int isAdjacent;
            scanf("%d", &isAdjacent);
            if (isAdjacent)
                addEdge(graph, i, j);
        }
    }

    printGraph(graph);

    // Perform topological sort
    topologicalSort(graph);

    return 0;
}
