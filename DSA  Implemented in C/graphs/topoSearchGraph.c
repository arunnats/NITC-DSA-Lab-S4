#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Stack
{
    int array[MAX_NODES];
    int top;
};

struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

void push(struct Stack *stack, int data)
{
    stack->array[++stack->top] = data;
}

int pop(struct Stack *stack)
{
    return stack->array[stack->top--];
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to perform depth-first search
int isCyclicUtil(int v, int graph[][100], int visited[], int recStack[])
{
    if (visited[v] == 0)
    {
        visited[v] = 1;
        recStack[v] = 1;

        for (int i = 0; i < MAX_NODES; ++i)
        {
            if (graph[v][i])
            {
                if (!visited[i] && isCyclicUtil(i, graph, visited, recStack))
                {
                    return 1;
                }
                else if (recStack[i])
                {
                    return 1;
                }
            }
        }
    }
    recStack[v] = 0; // Remove the vertex from recursion stack
    return 0;
}

// Function to check if the graph is cyclic
int isCyclic(int graph[][100], int m)
{
    int visited[MAX_NODES] = {0};
    int recStack[MAX_NODES] = {0};

    for (int i = 0; i < m; ++i)
    {
        if (isCyclicUtil(i, graph, visited, recStack))
        {
            return 1;
        }
    }
    return 0;
}

// Function to print the topological sort
void printTopologicalSort(int v, int graph[][100], int visited[], struct Stack *stack)
{
    visited[v] = 1;
    for (int i = 0; i < MAX_NODES; ++i)
    {
        if (graph[v][i] && !visited[i])
        {
            printTopologicalSort(i, graph, visited, stack);
        }
    }
    push(stack, v);
}

void topologicalSort(int graph[][100], int m)
{
    int visited[MAX_NODES] = {0};
    struct Stack *stack = createStack();

    for (int i = 0; i < m; ++i)
    {
        if (!visited[i])
        {
            printTopologicalSort(i, graph, visited, stack);
        }
    }

    printf("Topological sort: ");

    while (!isEmpty(stack))
    {
        printf("%d ", pop(stack));
    }
    printf("\n");
}

void printGraph(int graph[][100], int m)
{
    printf("Adjacency matrix \n");

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m;
    scanf("%d", &m);

    int graph[MAX_NODES][100];

    int label, adj;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &label);
            graph[i][j] = label;
        }
    }

    printGraph(graph, m);

    if (isCyclic(graph, m))
    {
        printf("The graph is cyclic.\n");
    }
    else
    {
        printf("The graph is acyclic.\n");
        printf("Performing topological sorting:\n");
        topologicalSort(graph, m);
    }

    return 0;
}
