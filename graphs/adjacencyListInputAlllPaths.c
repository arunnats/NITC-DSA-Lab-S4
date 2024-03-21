#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A structure to represent a node in the adjacency list
struct node
{
    int vertex;
    struct node *next;
};

// A structure to represent the adjacency list
struct adj_list
{
    struct node *head;
};

// A structure to represent the graph
struct graph
{
    int num_vertices;
    struct adj_list *adj_lists;
};

// Create a new node in the adjacency list
struct node *new_node(int vertex)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// Create a graph with n vertices
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

// Add an edge to the graph
void add_edge(struct graph *graph, int src, int dest)
{
    if (src >= 0 && src < graph->num_vertices && dest >= 0 && dest < graph->num_vertices)
    {
        // Add an edge from src to dest
        struct node *new_node1 = new_node(dest);
        new_node1->next = graph->adj_lists[src].head;
        graph->adj_lists[src].head = new_node1;
    }
    else
    {
        printf("Invalid edge: (%d, %d)\n", src, dest);
    }
}

// Utility function to print a path
void print_path(int path[], int path_len)
{
    for (int i = 0; i < path_len; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Recursive function to print all paths from 'src' to 'dest' in a graph
void print_all_paths_util(struct graph *graph, int src, int dest, int path[], int path_index, bool visited[])
{
    visited[src] = true;
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

    path_index--;
    visited[src] = false;
}

// Function to print all paths from 'src' to 'dest' in a graph
void print_all_paths(struct graph *graph, int src, int dest)
{
    bool *visited = (bool *)malloc(graph->num_vertices * sizeof(bool));
    int *path = (int *)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++)
    {
        visited[i] = false;
    }
    print_all_paths_util(graph, src, dest, path, 0, visited);
    free(visited);
    free(path);
}

int main()
{
    int m;
    scanf("%d", &m);
    struct graph *graph = create_graph(m);

    int label, adj;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label); // Read the label of the node
        while (scanf("%d", &adj) == 1)
        {
            add_edge(graph, label, adj); // Add an edge between label and adj
            char c = getchar();
            if (c == '\n')
                break; // End of line
        }
    }

    int start, end;
    scanf("%d %d", &start, &end); // Read start and end vertices

    if (start >= 0 && start < m && end >= 0 && end < m)
    {
        printf("All paths between %d and %d:\n", start, end);
        print_all_paths(graph, start, end); // Print all paths from start to end
    }
    else
    {
        printf("-1\n");
    }

    return 0;
}
