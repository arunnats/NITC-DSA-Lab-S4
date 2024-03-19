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

// DFS function to check if the graph contains a cycle
bool isCyclicUtil(struct Graph *graph, int v, bool visited[], bool *recStack)
{
    if (visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacent to this vertex
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            int adj = temp->destination;
            if (!visited[adj] && isCyclicUtil(graph, adj, visited, recStack))
                return true;
            else if (recStack[adj])
                return true;
            temp = temp->next;
        }
    }

    // Remove the vertex from recursion stack
    recStack[v] = false;
    return false;
}

// Function to check if the graph contains a cycle
bool isCyclic(struct Graph *graph)
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = (bool *)malloc(graph->V * sizeof(bool));
    bool *recStack = (bool *)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different DFS trees
    for (int i = 0; i < graph->V; i++)
        if (!visited[i] && isCyclicUtil(graph, i, visited, recStack))
            return true;

    return false;
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

    if (isCyclic(graph))
        printf("The graph contains a cycle.\n");
    else
        printf("The graph does not contain a cycle.\n");

    return 0;
}
