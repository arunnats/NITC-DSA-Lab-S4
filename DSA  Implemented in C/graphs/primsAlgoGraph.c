#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Node
{
    int weight;
    int vertex;
    int parent;
    struct Node *next;
};

void printGraph(int graph[][100], int m)
{
    printf("Adjacency matrix \n");

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

struct Node *createNode(int weight, int vertex, int parent)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));

    newnode->weight = weight;
    newnode->vertex = vertex;
    newnode->parent = parent;
    newnode->next = NULL;

    return newnode;
}

struct Node *insert(struct Node *head, int weight, int vertex, int parent)
{

    struct Node *newnode = createNode(weight, vertex, parent);

    if (head == NULL)
    {
        head = newnode;
        return head;
    }

    struct Node *temp = head;
    if (temp->weight > weight)
    {
        head = newnode;
        head->next = temp;
        return head;
    }

    while (temp->next != NULL)
    {
        if (temp->next->weight > weight)
        {
            newnode->next = temp->next;
            temp->next = newnode;
            break;
        }
        temp = temp->next;
    }

    if (temp->next == NULL)
        temp->next = newnode;

    return head;
}

void primsAlgo(int graph[MAX_NODES][100], struct Node *head, int start_vertex, int n)
{

    int visited[n];
    int weightSum = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    if (head == NULL)
        head = createNode(0, start_vertex, -1);

    while (head != NULL)
    {
        struct Node *temp = head;
        head = head->next;
        int current = temp->vertex;

        if (visited[current] == 0)
        {
            if (temp->parent != -1)
            {
                printf("%d %d ", temp->parent, temp->vertex);
                weightSum = weightSum + temp->weight;
            }
            for (int i = 0; i < n; i++)
            {
                if (graph[current][i] != 0)
                {
                    head = insert(head, graph[current][i], i, current);
                }
            }
        }

        visited[current] = 1;
    }

    printf("\n%d \n", weightSum);
}

int main()
{
    int m;
    scanf("%d", &m);
    struct Node *head = NULL;

    int graph[MAX_NODES][100];

    int label;

    // Read the adjacency list and edge weights
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &label);
            graph[i][j] = label;
        }
    }

    printGraph(graph, m);

    int startVertex;
    printf("Enter the starting node for Prim's algorithm: ");
    scanf("%d", &startVertex);

    primsAlgo(graph, head, startVertex, m);

    return 0;
}
