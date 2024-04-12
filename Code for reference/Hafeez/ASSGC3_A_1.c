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

int min(int a, int b)
{
    return ((a > b) ? b : a);
}

void DFS(node **graph, int label, int n, int *size, int *flag)
{
    flag[label] = 1;

    *size = *size + 1;
    node *temp = graph[label]->next;

    while (temp != NULL)
    {
        if (flag[temp->label] == 0)
            DFS(graph, temp->label, n, size, flag);
        temp = temp->next;
    }
}

int connected_components(node **graph, int n, int size_print, int count_print)
{

    int flag[n + 1];

    for (int i = 0; i <= n; i++)
        flag[i] = 0;

    int count = 0;
    int size = 0;

    for (int i = 1; i <= n; i++)
    {
        if (flag[i] == 0 && graph[i]->next != NULL)
        {
            DFS(graph, i, n, &size, flag);
            if (size_print)
                printf("%d ", size);
            size = 0;
            count++;
        }
    }

    if (count_print)
        printf("%d\n", count);
    else
        printf("\n");
}

void DFS_bridge_articulation(node **graph, int label, int *parent, int *visited_time, int *low_time, int *flag, int *time, int *bridges, int *articulation)
{
    visited_time[label] = low_time[label] = ++(*time);
    flag[label] = 1;

    int children = 0;
    node *current = graph[label]->next;

    while (current != NULL)
    {
        int vertex = current->label;

        if (flag[vertex] == 0)
        {
            children++;
            if (parent[vertex] == -1)
                parent[vertex] = label;
            DFS_bridge_articulation(graph, vertex, parent, visited_time, low_time, flag, time, bridges, articulation);

            low_time[label] = min(low_time[label], low_time[vertex]);

            if (low_time[vertex] > visited_time[label])
                (*bridges)++;

            if (parent[label] == -1 && children > 1)
            {
                // printf( "%d " , label  );
                articulation[label] = 1;
            }

            if (parent[label] != -1 && low_time[vertex] >= visited_time[label])
            {
                // printf( "%d " , label  );
                articulation[label] = 1;
            }
        }

        else if (vertex != parent[label])
        {
            low_time[label] = min(low_time[label], visited_time[vertex]);
        }

        current = current->next;
    }
}

void find_bridges_articulation(node **graph, int n, int bridge_print, int art_print)
{
    int visited_time[n + 1];
    int low_time[n + 1];
    int parent[n + 1];
    int flag[n + 1];
    int time = 0;
    int bridges = 0;
    int articulation[n + 1];

    for (int i = 0; i <= n; i++)
    {
        visited_time[i] = 0;
        low_time[i] = 0;
        parent[i] = -1;
        flag[i] = 0;
        articulation[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (flag[i] == 0)
            DFS_bridge_articulation(graph, graph[i]->label, parent, visited_time, low_time, flag, &time, &bridges, articulation);
    }
    int count = 0;

    if (art_print)
    {
        for (int i = 0; i <= n; i++)
            if (articulation[i] == 1)
                count++;
        printf("%d\n", count);
    }
    if (bridge_print)
        printf("%d\n", bridges);
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

    while (1)
    {
        scanf("%c", &c);

        switch (c)
        {
        case 'n':
        {
            connected_components(graph, n, 0, 1);
            break;
        }

        case 's':
        {
            connected_components(graph, n, 1, 0);
            break;
        }

        case 'b':
        {
            find_bridges_articulation(graph, n, 1, 0);
            break;
        }

        case 'a':
        {
            find_bridges_articulation(graph, n, 0, 1);
            break;
        }

        case 't':
            return 0;
        }
    }
}
