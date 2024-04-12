#include <stdio.h>
#include <stdlib.h>

struct node
{
    int label;
    struct node *next;
};

typedef struct node node;

node *create_node(int label)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->label = label;
    newnode->next = NULL;
}

void print(int *stack, int top)
{
    for (int i = 0; i < top; i++)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void DFS(node **graph, int *visited, int label, int end, int *stack, int top)
{

    visited[label] = 1;
    stack[top++] = label;
    node *temp = graph[label]->next;

    if (label == end)
        print(stack, top);
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

void all_path(node **graph, int start, int end, int n)
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

int isolated(node **graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (graph[i]->next == NULL)
            return 0;
    }
    return 1;
}

int DFS_cycle(node **graph, int label, int *visited, int n)
{

    visited[label] = 1;
    node *temp = graph[label]->next;

    return 0;
}

int cycle(node **graph, int n)
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
    node **graph;
    scanf("%d", &n);

    graph = (node **)malloc((n + 1) * sizeof(node *));

    for (int i = 0; i <= n; i++)
    {
        node *newnode = create_node(i);
        graph[i] = newnode;
    }

    int label;
    int adj;

    char c;
    int count = 0;
    while (scanf("%d", &label) == 1)
    {

        node *temp = graph[label];

        while (scanf("%d", &adj) == 1)
        {
            node *newnode = create_node(adj);
            temp->next = newnode;
            temp = temp->next;
            char c = getchar();
            if (c == '\n')
                break;
        }
    }
    all_path(graph, 1, 4, n);
}