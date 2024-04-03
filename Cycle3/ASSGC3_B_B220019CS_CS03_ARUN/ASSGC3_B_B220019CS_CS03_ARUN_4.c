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
    graph->adjMatrix[dest][src] = weight;
}

struct Graph *floydWarshall(struct Graph *graph)
{
    int numVertices = graph->numVertices;

    struct Graph *resultGraph = createGraph(numVertices);

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (graph->adjMatrix[i][j] != -1)
                resultGraph->adjMatrix[i][j] = graph->adjMatrix[i][j];
            else
                resultGraph->adjMatrix[i][j] = 9999;
        }
    }

    for (int k = 0; k < numVertices; k++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            for (int i = 0; i < numVertices; i++)
            {
                if (resultGraph->adjMatrix[i][j] > resultGraph->adjMatrix[i][k] + resultGraph->adjMatrix[k][j])
                {
                    resultGraph->adjMatrix[i][j] = resultGraph->adjMatrix[i][k] + resultGraph->adjMatrix[k][j];
                }
            }
        }
    }

    return resultGraph;
}

void printGraph(struct Graph *graph)
{

    for (int i = 0; i < graph->numVertices; ++i)
    {

        for (int j = 0; j < graph->numVertices; ++j)
        {

            printf("%d ", graph->adjMatrix[i][j]);
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

    struct Graph *resultGraph = floydWarshall(graph);

    printGraph(resultGraph);

    return 0;
}
