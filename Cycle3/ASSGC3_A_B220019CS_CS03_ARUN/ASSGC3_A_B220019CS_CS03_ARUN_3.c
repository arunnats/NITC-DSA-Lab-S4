#include <stdio.h>
#include <stdlib.h>

struct node
{
    int vertex;
    struct node *next;
};

struct adj_list
{
    struct node *head;
};

struct graph
{
    int num_vertices;
    struct adj_list *adj_lists;
};

struct node *new_node(int vertex)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

struct graph *create_graph(int n)
{
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph));
    graph->num_vertices = n;
    graph->adj_lists = (struct adj_list *)malloc(n * sizeof(struct adj_list));

    int i;
    for (i = 0; i < n; i++)
    {
        graph->adj_lists[i].head = NULL;
    }

    return graph;
}

void add_edge(struct graph *graph, int src, int dest)
{
    if (src >= 0 && src < graph->num_vertices && dest >= 0 && dest < graph->num_vertices)
    {
        struct node *new_node1 = new_node(dest);
        new_node1->next = graph->adj_lists[src].head;
        graph->adj_lists[src].head = new_node1;
    }
    else
    {
        printf("Invalid edge: (%d, %d)\n", src, dest);
    }
}

int has_cycle_util(struct graph *graph, int v, int visited[], int parent)
{
    visited[v] = 1;

    struct node *temp = graph->adj_lists[v].head;
    while (temp != NULL)
    {
        int adj_vertex = temp->vertex;

        if (!visited[adj_vertex])
        {
            if (has_cycle_util(graph, adj_vertex, visited, v))
                return 1;
        }
        else if (adj_vertex != parent)
            return 1;

        temp = temp->next;
    }

    return 0;
}

int has_cycle(struct graph *graph)
{
    int *visited = (int *)malloc(graph->num_vertices * sizeof(int));

    for (int i = 0; i < graph->num_vertices; i++)
        visited[i] = 0;

    for (int v = 0; v < graph->num_vertices; v++)
    {
        if (!visited[v])
        {
            if (has_cycle_util(graph, v, visited, -1))
            {
                free(visited);
                return 1;
            }
        }
    }

    free(visited);
    return 0;
}

void mark_reachable_vertices(struct graph *graph, int v, int visited[])
{
    visited[v] = 1;

    struct node *temp = graph->adj_lists[v].head;
    while (temp != NULL)
    {
        int adj_vertex = temp->vertex;
        if (!visited[adj_vertex])
            mark_reachable_vertices(graph, adj_vertex, visited);
        temp = temp->next;
    }
}

int is_every_vertex_reachable(struct graph *graph, int root)
{
    int *visited = (int *)malloc(graph->num_vertices * sizeof(int));

    for (int i = 0; i < graph->num_vertices; i++)
        visited[i] = 0;

    mark_reachable_vertices(graph, root, visited);

    for (int i = 0; i < graph->num_vertices; i++)
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

int has_isolated_vertices(struct graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (graph->adj_lists[i].head == NULL)
            return 1;
    }
    return 0;
}

int valid_tree(struct graph *graph)
{
    if (has_cycle(graph))
        return -1;

    if (!is_every_vertex_reachable(graph, 0))
        return -1;

    if (has_isolated_vertices(graph))
        return -1;

    return 1;
}

void print_path(int path[], int path_len)
{
    for (int i = 0; i < path_len; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void print_all_paths_util(struct graph *graph, int src, int dest, int path[], int path_index, int visited[])
{
    visited[src] = 1;
    path[path_index] = src;
    path_index++;

    if (src == dest)
    {
        print_path(path, path_index);
    }
    else
    {
        struct node *temp = graph->adj_lists[src].head;
        while (temp != NULL)
        {
            if (!visited[temp->vertex])
            {
                print_all_paths_util(graph, temp->vertex, dest, path, path_index, visited);
            }
            temp = temp->next;
        }
    }

    visited[src] = 0; // Resetting visited for backtracking
    path_index--;     // Decrementing path_index for backtracking
}

void print_all_paths(struct graph *graph, int src, int dest)
{
    int *visited = (int *)malloc(graph->num_vertices * sizeof(int));
    int *path = (int *)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++)
    {
        visited[i] = 0;
    }
    print_all_paths_util(graph, src, dest, path, 0, visited);
    free(visited);
    free(path);
}

int main()
{
    int N;
    scanf("%d", &N);
    struct graph *graph = create_graph(N);

    int label, adj;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &label);
        while (scanf("%d", &adj) == 1)
        {
            add_edge(graph, label, adj);
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

            if (start >= 0 && start < N && end >= 0 && end < N)
            {
                print_all_paths(graph, start, end);
            }
            else
            {
                printf("-1\n");
            }
            break;

        case 't':
            printf("%d \n", valid_tree(graph));
            break;

        case 'x':
            break;

        default:
            break;
        }

    } while (choice != 'x');

    return 1;
}
