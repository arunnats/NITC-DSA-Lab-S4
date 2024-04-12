#include <stdio.h>
#include <stdlib.h>

struct GraphEdge
{
    int dest;
    int weight;
    struct GraphEdge *next;
};

struct Graph
{
    int numVertices;
    struct GraphEdge **adjLists;
};

struct Graph *createGraph(int numVertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct GraphEdge **)malloc(numVertices * sizeof(struct GraphEdge *));

    for (int i = 0; i < numVertices; ++i)
    {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    struct GraphEdge *newEdge = (struct GraphEdge *)malloc(sizeof(struct GraphEdge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->adjLists[src];
    graph->adjLists[src] = newEdge;
}

void printGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        struct GraphEdge *temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d\n", i);

        while (temp)
        {
            printf(" -> %d(weight: %d)", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf(" -> NULL\n");
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

    printGraph(graph);

    return 0;
}
