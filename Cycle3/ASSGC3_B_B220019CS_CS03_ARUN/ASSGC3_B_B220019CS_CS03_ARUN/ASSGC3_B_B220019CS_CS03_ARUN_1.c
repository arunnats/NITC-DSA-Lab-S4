#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int weight;
    int vertex;
    int parent;
    struct Node *next;
};

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

struct Graph *createGraph(int numVertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; ++i)
    {
        graph->adjMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; ++j)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
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

int primsAlgo(struct Graph *graph, struct Node *head, int start_vertex, int n, int ch)
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
                if (ch == 1)
                    printf("%d %d ", temp->parent, temp->vertex);
                if (ch == 0)
                    weightSum = weightSum + temp->weight;
            }
            for (int i = 0; i < n; i++)
            {
                if (graph->adjMatrix[current][i] != 0)
                {
                    head = insert(head, graph->adjMatrix[current][i], i, current);
                }
            }
        }

        visited[current] = 1;
    }

    return weightSum;
}

int main()
{

    struct Node *head = NULL;

    int m;
    scanf("%d", &m);
    struct Graph *graph = createGraph(m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int weight;
            scanf("%d", &weight);
            if (weight)
                addEdge(graph, i, j, weight);
        }
    }

    int weight;
    int i = 0;
    char c;
    char ch[100];

    while (1)
    {
        scanf("%c", &c);
        switch (c)
        {
        case 't':
        {
            printf("%d\n", primsAlgo(graph, head, 0, graph->numVertices, 0));
            break;
        }

        case 's':
        {
            int startVertex = 0;
            while (c != ')')
            {
                scanf("%c", &c);
                if (c != '(' && c != ')')
                {
                    startVertex = startVertex * 10 + (c - '0');
                }
            }

            if (startVertex >= graph->numVertices || startVertex < 0)
            {
                printf("-1\n");
                break;
            }

            primsAlgo(graph, head, startVertex, graph->numVertices, 1);
            printf("\n");
            break;
        }

        case 'x':
            return 0;
        }
    }
}