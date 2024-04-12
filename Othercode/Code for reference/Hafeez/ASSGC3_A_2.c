#include <stdio.h>
#include <stdlib.h>

int DFS_cycle(int graph[][100], int label, int *visited, int *rec_stack, int n)
{

    visited[label] = 1;
    rec_stack[label] = 1;

    for (int i = 1; i <= n; i++)
    {

        if (graph[label][i] == 1)
        {
            if (visited[i] == 0)
            {
                if (DFS_cycle(graph, i, visited, rec_stack, n))
                    return 1;
            }
            else if (rec_stack[i] == 1)
                return 1;
        }
    }

    rec_stack[label] = 0;
    return 0;
}

int cycle(int graph[][100], int n)
{

    int visited[n + 1];
    int rec_stack[n + 1];

    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
        rec_stack[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            if (DFS_cycle(graph, i, visited, rec_stack, n))
                return 1;
        }
    }

    return 0;
}

void DFS_stack(int graph[][100], int label, int *visited, int *stack, int *top, int n)
{
    visited[label] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (graph[label][i] == 1 && visited[i] == 0)
        {
            DFS_stack(graph, i, visited, stack, top, n);
        }
    }

    stack[(*top)++] = label;
}

void DFS(int graph[][100], int label, int *visited, int n)
{
    visited[label] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (graph[label][i] == 1 && visited[i] == 0)
        {
            DFS(graph, i, visited, n);
        }
    }
}

int scc(int graph[][100], int n)
{
    int stack[n];
    int visited[n + 1];
    int top = 0;

    for (int i = 0; i <= n; i++)
        visited[i] = 0;

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
            DFS_stack(graph, i, visited, stack, &top, n);
    }

    for (int i = 0; i <= n; i++)
        visited[i] = 0;

    int graph_reverse[n + 1][100];

    // reversing the graph
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (graph[i][j] == 1)
            {
                graph_reverse[j][i] = 1;
            }
        }
    }

    int scc = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (visited[stack[i]] == 0)
        {
            scc++;
            DFS(graph_reverse, stack[i], visited, n);
        }
    }

    return scc;
}

int main()
{
    int n;
    scanf("%d", &n);

    int graph[n + 1][100];

    int label = 1;
    int edge;
    int i = 1;
    char c;

    while (label <= n)
    {
        scanf("%d", &edge);
        graph[label][i++] = edge;
        char c = getchar();
        if (c == '\n')
        {
            i = 1;
            label++;
        }
    }

    while (1)
    {
        scanf("%c", &c);

        switch (c)
        {
        case 't':
        {
            if (!cycle(graph, n))
                printf("%d\n", 1);
            else
                printf("%d\n", -1);
            break;
        }

        case 'c':
        {
            printf("%d\n", scc(graph, n));
            break;
        }

        case 'x':
            return 0;
        }
    }
}