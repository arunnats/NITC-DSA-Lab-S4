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
            return 1;
    }
    return 0;
}

// Function prototype for markReachableVertices
void markReachableVertices(Graph *graph, int v, int visited[]);

int isEveryVertexReachable(Graph *graph, int root)
{
    int visited[graph->size + 1];
    for (int i = 0; i <= graph->size; i++)
    {
        visited[i] = 0;
    }
    markReachableVertices(graph, root, visited);
    for (int i = 1; i <= graph->size; i++)
    {
        if (!visited[i])
        {
            return 0;
        }
    }
    return 1;
}

void markReachableVertices(Graph *graph, int v, int visited[])
{
    visited[v] = 1;
    Node *temp = graph->graph[v]->next;
    while (temp != NULL)
    {
        int adj_vertex = temp->label;
        if (!visited[adj_vertex])
        {
            markReachableVertices(graph, adj_vertex, visited);
        }
        temp = temp->next;
    }
}

int DFSForCycle(Graph *graph, int label, int *visited, int parent)
{
    visited[label] = 1;
    Node *temp = graph->graph[label]->next;

    while (temp != NULL)
    {
        if (!visited[temp->label])
        {
            if (DFSForCycle(graph, temp->label, visited, label))
                return 1;
        }
        else if (temp->label != parent)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int hasCycle(Graph *graph)
{
    int visited[graph->size + 1];
    for (int i = 0; i <= graph->size; i++)
    {
        visited[i] = 0;
    }

    for (int i = 1; i <= graph->size; i++)
    {
        if (visited[i] == 0)
        {
            if (DFSForCycle(graph, i, visited, -1))
                return 1;
        }
    }
    return 0;
}

int isValidTree(Graph *graph)
{
    if (hasCycle(graph))
        return 0;

    if (!isEveryVertexReachable(graph, 1))
        return 0;

    if (isIsolated(graph))
        return 0;

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

    int start, end;
    char choice;

    do
    {
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'a':
            scanf("%d %d", &start, &end);
            if (start >= 0 && start <= n && end >= 0 && end <= n)
            {
                findAllPaths(&graph, start, end);
            }
            else
            {
                printf("-1\n");
            }
            break;

        case 't':
            if (isValidTree(&graph))
                printf("1\n");
            else
                printf("-1\n");
            break;

        case 'x':
            break;

        default:
            break;
        }

    } while (choice != 'x');

    return 0;
}
