#include <stdio.h>
#include <stdlib.h>

struct graph_node
{
    int label;
    struct adjacency_list *adj_list;
};

struct adjacency_list
{
    int vertex;
    struct adjacency_list *next;
};

typedef struct graph_node GraphNode;
typedef struct adjacency_list AdjacencyList;

GraphNode *create_graph_node(int label)
{
    GraphNode *new_node = (GraphNode *)malloc(sizeof(GraphNode));
    new_node->label = label;
    new_node->adj_list = NULL;
    return new_node;
}

void print_stack(int *stack, int top)
{
    for (int i = 0; i < top; i++)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void DFS(GraphNode **graph, int *visited, int label, int end, int *stack, int top)
{
    visited[label] = 1;
    stack[top++] = label;
    AdjacencyList *temp = graph[label]->adj_list;

    if (label == end)
        print_stack(stack, top);
    else
    {
        while (temp != NULL)
        {
            if (visited[temp->vertex] == 0)
                DFS(graph, visited, temp->vertex, end, stack, top);
            temp = temp->next;
        }
    }

    top--;
    visited[label] = 0;
}

void all_paths(GraphNode **graph, int start, int end, int n)
{
    int visited[n + 1];
    int stack[n];
    int top = 0;

    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
    }

    DFS(graph, visited, start, end, stack, top);
}

int is_isolated(GraphNode **graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (graph[i]->adj_list == NULL)
            return 0;
    }
    return 1;
}

int DFS_cycle(GraphNode **graph, int label, int *visited, int n)
{
    visited[label] = 1;
    AdjacencyList *temp = graph[label]->adj_list;
    return 0; // You need to implement the cycle detection logic
}

int has_cycle(GraphNode **graph, int n)
{
    int visited[n + 1];

    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            if (DFS_cycle(graph, i, visited, n))
                return 1;
        }
    }

    return 0;
}

int main()
{
    int n;
    GraphNode **graph;
    scanf("%d", &n);

    graph = (GraphNode **)malloc((n + 1) * sizeof(GraphNode *));

    for (int i = 0; i <= n; i++)
    {
        GraphNode *new_node = create_graph_node(i);
        graph[i] = new_node;
    }

    int label;
    int adj;

    char c;
    while (scanf("%d", &label) == 1)
    {
        AdjacencyList *temp = graph[label]->adj_list;
        while (scanf("%d", &adj) == 1)
        {
            AdjacencyList *new_node = (AdjacencyList *)malloc(sizeof(AdjacencyList));
            new_node->vertex = adj;
            new_node->next = NULL;
            if (temp == NULL)
            {
                graph[label]->adj_list = new_node;
                temp = new_node;
            }
            else
            {
                temp->next = new_node;
                temp = temp->next;
            }
            char c = getchar();
            if (c == '\n')
                break;
        }
    }
    all_paths(graph, 1, 4, n);

    // Free memory
    for (int i = 0; i <= n; i++)
    {
        AdjacencyList *temp = graph[i]->adj_list;
        while (temp != NULL)
        {
            AdjacencyList *next = temp->next;
            free(temp);
            temp = next;
        }
        free(graph[i]);
    }
    free(graph);

    return 0;
}
