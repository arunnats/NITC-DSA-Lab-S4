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
        printf("Node %d -> ", v);
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            printf("%d ", temp->destination);
            temp = temp->next;
        }
        printf("\n");
    }
}

int isCyclicUtil(struct Graph *graph, int v, int *visited, int *recStack)
{
    if (visited[v] == 0)
    {
        visited[v] = 1;
        recStack[v] = 1;

        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            int adj = temp->destination;
            if (visited[adj] == 0 && isCyclicUtil(graph, adj, visited, recStack))
                return 1;
            else if (recStack[adj] == 1)
                return 1;
            temp = temp->next;
        }
    }

    recStack[v] = 0;
    return 0;
}

int isCyclic(struct Graph *graph)
{
    int *visited = (int *)malloc(graph->V * sizeof(int));
    int *recStack = (int *)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++)
    {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < graph->V; i++)
        if (visited[i] == 0 && isCyclicUtil(graph, i, visited, recStack))
            return 1;

    return 0;
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
