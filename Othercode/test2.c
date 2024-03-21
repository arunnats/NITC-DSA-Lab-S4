#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int label;
    struct Node *next;
} Node;

typedef struct
{
    Node **graph;
    int size;
} Graph;

Node *createNode(int label)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->label = label;
        newNode->next = NULL;
    }
    return newNode;
}

void printStack(int *stack, int top)
{
    for (int i = 0; i < top; i++)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void DFS(Graph *graph, int *visited, int label, int end, int *stack, int top)
{
    visited[label] = 1;
    stack[top++] = label;
    Node *temp = graph->graph[label]->next;

    if (label == end)
        printStack(stack, top);
    else
    {
        while (temp != NULL)
        {
            if (visited[temp->label] == 0)
                DFS(graph, visited, temp->label, end, stack, top);
            temp = temp->next;
        }
    }

    top--;
    visited[label] = 0;
}

void findAllPaths(Graph *graph, int start, int end)
{
    int visited[graph->size + 1];
    int stack[graph->size];
    int top = 0;

    for (int i = 0; i <= graph->size; i++)
    {
        visited[i] = 0;
    }

    DFS(graph, visited, start, end, stack, top);
}

int isIsolated(Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (graph->graph[i]->next == NULL)
            return 0;
    }
    return 1;
}

int DFSForCycle(Graph *graph, int v, int visited[], int parent)
{
    visited[v] = 1;

    Node *temp = graph->graph[v]->next;
    while (temp != NULL)
    {
        int adj_vertex = temp->label;

        if (!visited[adj_vertex])
        {
            if (DFSForCycle(graph, adj_vertex, visited, v))
                return 1;
        }
        else if (adj_vertex != parent)
            return 1;

        temp = temp->next;
    }

    return 0;
}

int hasCycle(Graph *graph)
{
    int *visited = (int *)malloc(graph->size * sizeof(int));

    for (int i = 0; i < graph->size; i++)
        visited[i] = 0;

    for (int v = 0; v < graph->size; v++)
    {
        if (!visited[v])
        {
            if (DFSForCycle(graph, v, visited, -1))
            {
                free(visited);
                return 1;
            }
        }
    }

    free(visited);
    return 0;
}

void markReachableVertices(Graph *graph, int v, int visited[])
{
    visited[v] = 1;

    Node *temp = graph->graph[v]->next;
    while (temp != NULL)
    {
        int adj_vertex = temp->label;
        if (!visited[adj_vertex])
            markReachableVertices(graph, adj_vertex, visited);
        temp = temp->next;
    }
}

int isEveryVertexReachable(Graph *graph, int root)
{
    int *visited = (int *)malloc(graph->size * sizeof(int));

    for (int i = 0; i < graph->size; i++)
        visited[i] = 0;

    markReachableVertices(graph, root, visited);

    for (int i = 0; i < graph->size; i++)
    {
        if (!visited[i])
        {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

int hasIsolatedVertices(Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (graph->graph[i]->next == NULL)
            return 1;
    }
    return 0;
}

int isValidTree(Graph *graph)
{
    if (hasCycle(graph))
        return -1;

    if (!isEveryVertexReachable(graph, 0))
        return -1;

    if (hasIsolatedVertices(graph))
        return -1;

    return 1;
}

int main()
{
    int n;
    Graph graph;
    scanf("%d", &n);

    graph.size = n;
    graph.graph = (Node **)malloc((n + 1) * sizeof(Node *));
    if (graph.graph == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= n; i++)
    {
        Node *newNode = createNode(i);
        if (newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        graph.graph[i] = newNode;
    }

    int label, adj;
    while (scanf("%d", &label) == 1)
    {
        Node *temp = graph.graph[label];

        while (scanf("%d", &adj) == 1)
        {
            Node *newNode = createNode(adj);
            if (newNode == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }
            temp->next = newNode;
            temp = temp->next;
            char c = getchar();
            if (c == '\n')
                break;
        }
    }

    findAllPaths(&graph, 1, 4);
    return 0;
}
