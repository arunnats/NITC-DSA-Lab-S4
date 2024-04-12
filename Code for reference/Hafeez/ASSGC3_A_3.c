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

int DFS_cycle(node **graph, int *parent, int label, int *visited)
{

    visited[label] = 1;
    node *temp = graph[label]->next;

    while (temp != NULL)
    {
        // if (visited[temp->label] == 1) {
        //     return 1;
        // }
        if (parent[temp->label] == -1)
            parent[temp->label] = label;
        if (visited[temp->label] == 0)
        {
            if (DFS_cycle(graph, parent, temp->label, visited))
                return 1;
        }
        else if (temp->label != parent[label])
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

int cycle(node **graph, int n)
{

    int visited[n + 1];
    int parent[n + 1];
    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            if (DFS_cycle(graph, parent, i, visited))
                return 1;
        }
    }

    return 0;
}

void DFS_reach(node **graph, int label, int *visited)
{
    visited[label] = 1;
    node *temp = graph[label]->next;

    while (temp != NULL)
    {
        if (visited[temp->label] == 0)
        {
            DFS_reach(graph, temp->label, visited);
        }
        temp = temp->next;
    }
}

int reachable(node **graph, int n)
{
    int visited[n + 1];

    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
    }

    DFS_reach(graph, 0, visited);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            return 0;
    }

    return 1;
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

    int a, b;
    while (1)
    {
        scanf("%c", &c);

        switch (c)
        {
        case 'a':
        {
            scanf("%d %d", &a, &b);
            all_path(graph, a, b, n);
            break;
        }
        case 't':
        {
            if (isolated(graph, n) && reachable(graph, n) && !cycle(graph, n))
                printf("%d\n", 1);
            else
                printf("%d\n", -1);
            break;
        }
        case 'x':
            return 0;
        }
    }
}
