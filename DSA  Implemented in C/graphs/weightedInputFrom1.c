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
    for (int i = 1; i < V; ++i)
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

    for (int i = 1; i <= count; i++)
    {
        temp = temp->next;
    }
    temp->weight = weight;
}

void printGraph(struct Graph *graph)
{
    printf("Adjacency List Representation of the Graph:\n");
    for (int v = 1; v < graph->V; ++v)
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

int main()
{
    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m + 1); // Increase size by 1 to accommodate node 0

    int label, adj;
    for (int i = 1; i <= m; ++i) // Start from 1
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

    for (int i = 1; i <= m; ++i) // Start from 1
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

    return 0;
}
