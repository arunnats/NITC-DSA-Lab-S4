#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

struct Graph *createGraph(int numVertices);
void addEdge(struct Graph *graph, int src, int dest, int weight);
void printMST(int parent[], struct Graph *graph);
void primMST(struct Graph *graph, int startNode, int ch);
void printGraph(struct Graph *graph); // Function prototype

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
    graph->adjMatrix[dest][src] = weight; // Undirected graph, so add edge both ways
}

void printMST(int parent[], struct Graph *graph)
{
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->numVertices; i++)
        printf("%d - %d    %d \n", parent[i], i, graph->adjMatrix[i][parent[i]]);
}

int minKey(int key[], int mstSet[], int numVertices)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < numVertices; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(struct Graph *graph, int startNode, int ch)
{
    int parent[graph->numVertices];
    int key[graph->numVertices];
    int mstSet[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[startNode] = 0;
    // parent[startNode] = -1;

    parent[startNode] = -1; // Initialize to -1 to signify no parent initially
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->adjMatrix[startNode][i] != 0 && i != startNode)
        {
            parent[startNode] = i;
            break;
        }
    }

    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        int u = minKey(key, mstSet, graph->numVertices);
        mstSet[u] = 1;
        for (int v = 0; v < graph->numVertices; v++)
            if (graph->adjMatrix[u][v] && mstSet[v] == 0 && graph->adjMatrix[u][v] < key[v])
                parent[v] = u, key[v] = graph->adjMatrix[u][v];
    }

    if (ch == 0)
        printMST(parent, graph);
    else if (ch == 1)
        printGraph(graph);
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

    char choice;
    while (1)
    {
        scanf(" %c", &choice);
        if (choice == 's')
            primMST(graph, 3, 1);
        else if (choice == 't')
            primMST(graph, 3, 0);
        else if (choice == 'p')
            printGraph(graph);
        else if (choice == 'e')
            break;
    }

    return 0;
}
