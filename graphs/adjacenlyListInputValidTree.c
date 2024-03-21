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

// Helper function for DFS to detect cycles
bool has_cycle_util(struct graph *graph, int v, bool visited[], int parent)
{
    visited[v] = true;

    // Recur for all adjacent vertices
    struct node *temp = graph->adj_lists[v].head;
    while (temp != NULL)
    {
        int adj_vertex = temp->vertex;

        if (!visited[adj_vertex])
        {
            if (has_cycle_util(graph, adj_vertex, visited, v))
                return true;
        }
        else if (adj_vertex != parent) // If the adjacent vertex is visited and not the parent of the current vertex, there is a cycle
            return true;

        temp = temp->next;
    }

    return false;
}

// Function to check for cycles (loops) in the graph
bool has_cycle(struct graph *graph)
{
    bool *visited = (bool *)malloc(graph->num_vertices * sizeof(bool));

    // Initialize all vertices as not visited
    for (int i = 0; i < graph->num_vertices; i++)
        visited[i] = false;

    // Call the helper function to detect cycles using DFS
    for (int v = 0; v < graph->num_vertices; v++)
    {
        if (!visited[v])
        {
            if (has_cycle_util(graph, v, visited, -1))
            {
                free(visited);
                return true;
            }
        }
    }

    free(visited);
    return false;
}

// Helper function for DFS to mark reachable vertices from the root
void mark_reachable_vertices(struct graph *graph, int v, bool visited[])
{
    visited[v] = true;

    // Recur for all adjacent vertices
    struct node *temp = graph->adj_lists[v].head;
    while (temp != NULL)
    {
        int adj_vertex = temp->vertex;
        if (!visited[adj_vertex])
            mark_reachable_vertices(graph, adj_vertex, visited);
        temp = temp->next;
    }
}

// Function to check if every vertex is reachable from the root
bool is_every_vertex_reachable(struct graph *graph, int root)
{
    bool *visited = (bool *)malloc(graph->num_vertices * sizeof(bool));

    // Initialize all vertices as not visited
    for (int i = 0; i < graph->num_vertices; i++)
        visited[i] = false;

    // Mark all reachable vertices from the root using DFS
    mark_reachable_vertices(graph, root, visited);

    // Check if all vertices are marked as visited
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (!visited[i])
        {
            free(visited);
            return false;
        }
    }

    free(visited);
    return true;
}

// Function to check for isolated vertices
bool has_isolated_vertices(struct graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (graph->adj_lists[i].head == NULL)
            return true; // If a vertex has no adjacent vertices, it is isolated
    }
    return false;
}

// Function to check if the given graph is a valid tree
int valid_tree(struct graph *graph)
{
    // Check for cycles
    if (has_cycle(graph))
        return -1;

    // Check if every vertex is reachable from the root
    if (!is_every_vertex_reachable(graph, 0))
        return -1;

    // Check for isolated vertices
    if (has_isolated_vertices(graph))
        return -1;

    return 1;
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

    printf("%d \n", valid_tree(graph));

    return 0;
}
