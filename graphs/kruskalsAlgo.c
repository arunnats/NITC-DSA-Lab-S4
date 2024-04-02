#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

struct Node
{
    int destination;
    int weight;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    int V;
    struct List *array;
};

struct Edge
{
    int source;
    int destination;
    int weight;
};

struct EdgeList
{
    struct Edge edges[999];
    int num_edges;
};

struct Subset
{
    int parent;
    int rank;
};

struct Node *createNode(int destination)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->destination = destination;
    newNode->weight = -1;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct List *)malloc(V * sizeof(struct List));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// void addEdge(struct Graph *graph, int source, int destination)
// {
//     struct Node *newNode = createNode(destination);
//     newNode->next = graph->array[source].head;
//     graph->array[source].head = newNode;
// }

void addEdge(struct Graph *graph, int source, int destination)
{
    struct Node *newNode = createNode(destination);
    struct Node *temp = graph->array[source].head;
    if (temp == NULL)
    {
        graph->array[source].head = newNode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void createEdge(struct EdgeList *edgeList, int source, int destination, int weight)
{
    if (edgeList->num_edges < 999)
    {
        edgeList->edges[edgeList->num_edges].source = source;
        edgeList->edges[edgeList->num_edges].destination = destination;
        edgeList->edges[edgeList->num_edges].weight = weight;
        edgeList->num_edges++;
    }
    else
    {
        printf("Edge list is full. Cannot add more edges.\n");
    }
}

struct EdgeList *createEdgeList(struct Graph *graph)
{
    // Allocate memory for the EdgeList
    struct EdgeList *edgeList = (struct EdgeList *)malloc(sizeof(struct EdgeList));

    edgeList->num_edges = 0;

    for (int i = 0; i < graph->V; ++i)
    {
        struct Node *currentNode = graph->array[i].head;

        while (currentNode != NULL)
        {
            if (edgeList->num_edges < 999)
            {
                edgeList->edges[edgeList->num_edges].source = i;
                edgeList->edges[edgeList->num_edges].destination = currentNode->destination;
                edgeList->edges[edgeList->num_edges].weight = currentNode->weight;
                edgeList->num_edges++;
            }
            else
            {
                printf("Edge list is full. Cannot add more edges.\n");
                free(edgeList); // Free memory allocated for EdgeList
                return NULL;
            }

            currentNode = currentNode->next;
        }
    }

    return edgeList;
}

void sortEdgeList(struct EdgeList *edgeList)
{
    // Selection sort implementation
    for (int i = 0; i < edgeList->num_edges - 1; ++i)
    {
        int min_index = i;
        for (int j = i + 1; j < edgeList->num_edges; ++j)
        {
            if (edgeList->edges[j].weight < edgeList->edges[min_index].weight)
            {
                min_index = j;
            }
        }
        // Swap edges
        struct Edge temp = edgeList->edges[min_index];
        edgeList->edges[min_index] = edgeList->edges[i];
        edgeList->edges[i] = temp;
    }
}

void printEdgeList(struct EdgeList *edgeList)
{
    for (int i = 0; i < edgeList->num_edges; ++i)
    {
        printf("%d %d %d\n", edgeList->edges[i].source, edgeList->edges[i].destination, edgeList->edges[i].weight);
    }
}

void addWeight(struct Graph *graph, int source, int weight, int count)
{
    struct Node *temp = graph->array[source].head;

    // if (temp->weight == -1)
    // {
    //     printf("weight = %d\n", weight);
    //     printf("val = %d\n", temp->destination);
    //     temp->weight = weight;
    //     temp = temp->next;
    // }

    for (int i = 0; i < count; i++)
    {
        temp = temp->next;
    }
    temp->weight = weight;
}

void printGraph(struct Graph *graph)
{
    printf("Adjacency List Representation of the Graph:\n");
    for (int v = 0; v < graph->V; ++v)
    {
        printf("Node %d -> ", v);
        struct Node *temp = graph->array[v].head;
        while (temp)
        {
            printf("(%d, %d) ", temp->destination, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void KruskalMST(struct EdgeList *edgeList, int V)
{
    struct Edge result[V];
    int e = 0;
    int i = 0;

    // Allocate memory for creating V subsets
    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));

    // Initialize subsets for each vertex
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < edgeList->num_edges)
    {
        // Pick the smallest edge
        struct Edge next_edge = edgeList->edges[i++];

        int x = find(subsets, next_edge.source);
        int y = find(subsets, next_edge.destination);

        // If including this edge does't cause cycle, include it
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("Edges in MST:\n");
    for (i = 0; i < e; ++i)
    {
        printf("%d - %d : %d\n", result[i].source, result[i].destination, result[i].weight);
    }

    free(subsets);
}

int main()
{
    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m);

    int label, adj;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label); // Read the label of the node
        while (scanf("%d", &adj) == 1)
        {
            addEdge(graph, label, adj);
            char c = getchar();
            if (c == '\n')
                break; // End of line
        }
    }

    // printGraph(graph);

    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label); // Read the label of the node
        int weight;
        int count = 0;
        while (scanf("%d", &weight) == 1)
        {
            addWeight(graph, label, weight, count);
            count++;

            // printf("weight: %d\n", weight);
            char c = getchar();
            if (c == '\n')
                break; // End of line
        }
    }

    printGraph(graph);

    printf("\n");

    struct EdgeList *edgeList = createEdgeList(graph);

    printEdgeList(edgeList);

    sortEdgeList(edgeList);

    printf("\n");
    printEdgeList(edgeList);

    printf("\n");

    KruskalMST(edgeList, m);

    return 0;
}