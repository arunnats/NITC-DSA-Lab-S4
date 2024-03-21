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

int BFSForSCC(struct Graph *graph, int start, int *visited)
{
    // Queue for BFS traversal
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

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

    return rear;
}

int numberOfStronglyConnectedComponents(struct Graph *graph)
{
    int visited[MAX_NODES] = {0};
    int components = 0;

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
    int N;
    scanf("%d", &N);

    struct Graph *graph = createGraph(N);

    char adjacencyMatrix[MAX_NODES][MAX_NODES + 1];
    for (int i = 0; i < N; ++i)
    {
        scanf("%s", adjacencyMatrix[i]);
    }

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

            if (isCyclic(graph))
                printf("1\n");
            else
                printf("-1\n");
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

    return 1;
}
