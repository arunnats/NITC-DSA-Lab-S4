#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

// Structure for a node in the adjacency list
struct Node
{
    int destination;
    struct Node *next;
};

// Structure for an adjacency list
struct List
{
    struct Node *head;
};

// Structure for the graph
struct Graph
{
    int V;
    struct List *array;
};

// Function to create a new node
struct Node *createNode(int destination)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->destination = destination;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct List *)malloc(V * sizeof(struct List));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int source, int destination)
{
    struct Node *newNode = createNode(destination);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
}

// Function to perform BFS traversal for finding strongly connected components
int BFSForSCC(struct Graph *graph, int start, int *visited)
{
    // Queue for BFS traversal
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Enqueue start vertex
    queue[rear++] = start;
    visited[start] = 1;

    // Perform BFS
    while (front < rear)
    {
        int v = queue[front++];
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            if (!visited[temp->destination])
            {
                queue[rear++] = temp->destination;
                visited[temp->destination] = 1;
            }
            temp = temp->next;
        }
    }

    return rear; // Return the number of vertices visited
}

// Function to calculate the number of strongly connected components
// Function to calculate the number of strongly connected components
int numberOfStronglyConnectedComponents(struct Graph *graph)
{
    int visited[MAX_NODES] = {0}; // Array to mark visited vertices
    int components = 0;           // Counter for number of components

    // Perform DFS traversal on all vertices
    for (int i = 0; i < graph->V; ++i)
    {
        if (!visited[i])
        {
            BFSForSCC(graph, i, visited);
            components++;
        }
    }

    return components;
}

int main()
{
    int N;
    scanf("%d", &N);

    // Create a graph with N vertices
    struct Graph *graph = createGraph(N);

    // Input the adjacency matrix
    char adjacencyMatrix[MAX_NODES][MAX_NODES + 1];
    for (int i = 0; i < N; ++i)
    {
        scanf("%s", adjacencyMatrix[i]);
    }

    // Construct the graph from the adjacency matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (adjacencyMatrix[i][j] == '1')
            {
                addEdge(graph, i, j);
            }
        }
    }

    char option;
    while (scanf(" %c", &option) == 1)
    {
        if (option == 't')
        {
            printf("%d\n", -1); // Placeholder for topological sort possibility
        }
        else if (option == 'c')
        {
            printf("%d\n", numberOfStronglyConnectedComponents(graph));
        }
        else if (option == 'x')
        {
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < graph->V; ++i)
    {
        struct Node *temp = graph->array[i].head;
        while (temp)
        {
            struct Node *toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
