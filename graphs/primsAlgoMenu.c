#include <stdio.h>
#include <stdlib.h>

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

int minKey(int key[], int mstSet[], int m)
{
    int min = 9999, min_index = -1;

    for (int v = 0; v < m; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMSTWeight(int parent[], struct Graph *graph)
{
    int weight = 0;
    for (int i = 1; i < graph->numVertices; i++)
        weight = weight + graph->adjMatrix[i][parent[i]];
    printf("%d\n", weight);
}

void printMSTEdges(int parent[], struct Graph *graph)
{
    for (int i = 1; i < graph->numVertices; i++)
        printf("%d %d ", parent[i], i);
}

void primMST(struct Graph *graph, int startNode, int ch)
{
    if (graph == NULL)
    {
        printf("-1\n");
        return;
    }

    // Check if startNode is valid
    if (startNode < 0 || startNode >= graph->numVertices)
    {
        printf("-1\n");
        return;
    }

    // Array to store constructed MST
    int m = graph->numVertices;
    int parent[m];
    int key[m];
    int mstSet[m];

    // Initialize all keys as INFINITE
    for (int i = 0; i < m; i++)
        key[i] = 9999, mstSet[i] = 0;

    // Set the key of the start node to 0
    key[startNode] = 0;
    parent[startNode] = -1;

    // The MST will have V vertices
    for (int count = 0; count < m - 1; count++)
    {
        int u = minKey(key, mstSet, m); // Pass 'm' as the number of vertices

        mstSet[u] = 1;

        for (int v = 0; v < m; v++)
        {
            if (graph->adjMatrix[u][v] && mstSet[v] == 0 && graph->adjMatrix[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph->adjMatrix[u][v];
            }
        }
    }

    // if (startNode != 0)
    // {
    //     int temp[m];
    //     for (int i = 0; i < m; i++)
    //         temp[i] = parent[i];
    //     for (int i = 0; i < m; i++)
    //         parent[i] = temp[(i + startNode) % m];
    // }

    // Check the value of 'ch' to decide which function to call for printing MST
    if (ch == 0)
        printMSTWeight(parent, graph);
    else if (ch == 1)
        printMSTEdges(parent, graph);
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
            primMST(graph, 0, 1);
        else if (choice == 't')
            primMST(graph, 0, 0);
        else if (choice == 'p')
            printGraph(graph);
        else if (choice == 'e')
            break;
    }

    return 0;
}