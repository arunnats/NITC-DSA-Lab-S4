#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

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

int minKey(int key[], bool mstSet[], int m)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < m; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
int printMST(int parent[], struct Graph *graph)
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < graph->numVertices; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph->adjMatrix[i][parent[i]]);
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(struct Graph *graph)
{
    // Array to store constructed MST
    int m = graph->numVertices;
    int parent[m];
    int key[m];
    bool mstSet[m];

    // Initialize all keys as INFINITE
    for (int i = 0; i < m; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    // The MST will have V vertices
    for (int count = 0; count < m - 1; count++)
    {
        int u = minKey(key, mstSet, m); // Pass 'm' as the number of vertices

        mstSet[u] = true;

        for (int v = 0; v < m; v++)
        {
            if (graph->adjMatrix[u][v] && mstSet[v] == false && graph->adjMatrix[u][v] < key[v])
                parent[v] = u, key[v] = graph->adjMatrix[u][v];
        }
    }

    printMST(parent, graph);
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

    primMST(graph);

    return 0;
}
