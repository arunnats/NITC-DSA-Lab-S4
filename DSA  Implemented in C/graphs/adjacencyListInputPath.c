#include <stdio.h>
#include <stdlib.h>

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
    int *visited;
    int *parent; // Array to store parent of each vertex during BFS
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
    graph->visited = (int *)malloc(n * sizeof(int));
    graph->parent = (int *)malloc(n * sizeof(int));

    int i;
    for (i = 0; i < n; i++)
    {
        graph->adj_lists[i].head = NULL;
        graph->visited[i] = 0;
        graph->parent[i] = -1; // Initialize parent of each vertex to -1
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

        // Add an edge from dest to src
        struct node *new_node2 = new_node(src);
        new_node2->next = graph->adj_lists[dest].head;
        graph->adj_lists[dest].head = new_node2;
    }
    else
    {
        printf("Invalid edge: (%d, %d)\n", src, dest);
    }
}

// BFS traversal of the graph starting from vertex v
void bfs(struct graph *graph, int start, int end)
{
    // Create a queue for BFS
    int queue[1000];
    int front = -1;
    int rear = -1;

    // Mark the start node as visited and enqueue it
    graph->visited[start] = 1;
    graph->parent[start] = -1; // Parent of start node is -1
    queue[++rear] = start;

    // Loop to visit all the vertices in the graph
    while (front != rear)
    {
        // Dequeue a vertex from the queue
        int current_vertex = queue[++front];

        // Check if the current vertex is the end vertex
        if (current_vertex == end)
            break; // Stop BFS if end vertex is reached

        // Get all the neighbors of the dequeued vertex
        struct node *temp = graph->adj_lists[current_vertex].head;
        while (temp != NULL)
        {
            int adj_vertex = temp->vertex;

            // If the neighbor has not been visited, mark it as visited, set its parent, and enqueue it
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                graph->parent[adj_vertex] = current_vertex;
                queue[++rear] = adj_vertex;
            }

            temp = temp->next;
        }
    }

    printf("Path from %d to %d : ", start, end);

    // Use a stack to store the vertices of the path
    int stack[1000];
    int top = -1;
    int current = end;
    while (current != -1)
    {
        stack[++top] = current;
        current = graph->parent[current];
    }

    // Pop elements from the stack to print the path in reverse order
    while (top >= 0)
    {
        printf("%d ", stack[top--]);
    }
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

    bfs(graph, start, end); // Perform BFS from start to end

    return 0;
}
