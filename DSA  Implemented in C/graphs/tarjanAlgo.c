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
        printf("Node %d -> ", v + 1);
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            printf("%d ", temp->destination + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

void tarjanDFS(struct Graph *graph, int u, int parent, int disc[], int low[], int articulation[], int *time)
{
    // Initialize discovery time and low value for current node
    disc[u] = low[u] = ++(*time);
    // Count children of current node in DFS tree
    int children = 0;

    // Traverse all adjacent vertices of the current vertex
    struct Node *v = graph->array[u].head;
    while (v != NULL)
    {
        int adj = v->destination;
        // If adj is not visited yet, process it
        if (disc[adj] == -1)
        {
            children++;
            // Update parent for the adjacent vertex
            tarjanDFS(graph, adj, u, disc, low, articulation, time);
            // Update low value of the current vertex for back edge
            low[u] = (low[u] < low[adj]) ? low[u] : low[adj];
            // Check if the current vertex is an articulation point
            if ((parent == -1 && children > 1) || (parent != -1 && low[adj] >= disc[u]))
                articulation[u] = 1;
        }
        // If adj is visited and not the parent of current vertex, update low value
        else if (adj != parent)
            low[u] = (low[u] < disc[adj]) ? low[u] : disc[adj];
        v = v->next;
    }
}

void findBridgesAndArticulationPoints(struct Graph *graph)
{
    int disc[MAX_NODES], low[MAX_NODES];
    int articulation[MAX_NODES] = {0};
    int time = 0;

    // Initialize discovery time and low value arrays
    for (int i = 0; i < graph->V; ++i)
    {
        disc[i] = -1;
        low[i] = -1;
    }

    // Perform DFS and identify bridges and articulation points
    for (int i = 0; i < graph->V; ++i)
    {
        if (disc[i] == -1)
            tarjanDFS(graph, i, -1, disc, low, articulation, &time);
    }

    // Count the number of bridges and articulation points
    int bridges = 0, articulationPoints = 0;
    for (int i = 0; i < graph->V; ++i)
    {
        if (articulation[i])
            articulationPoints++;

        struct Node *v = graph->array[i].head;
        while (v != NULL)
        {
            int adj = v->destination;
            if (low[adj] > disc[i])
                bridges++;
            v = v->next;
        }
    }

    printf("Number of bridges in the graph: %d\n", bridges);
    printf("Number of articulation points in the graph: %d\n", articulationPoints);
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

    findBridgesAndArticulationPoints(graph);

    return 0;
}
