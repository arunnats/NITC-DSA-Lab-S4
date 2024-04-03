#include <stdio.h>
#include <stdlib.h>

struct node
{
    int weight;
    int vertex;
    int parent;
    struct node *next;
};

typedef struct node node;

node *create_node(int weight, int vertex, int parent)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->weight = weight;
    newnode->vertex = vertex;
    newnode->parent = parent;
    newnode->next = NULL;

    return newnode;
}

node *insert(node *head, int weight, int vertex, int parent)
{

    node *newnode = create_node(weight, vertex, parent);

    if (head == NULL)
    {
        head = newnode;
        return head;
    }

    node *temp = head;
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

int primsAlgo(int graph[][100], node *head, int start_vertex, int n, int ch)
{

    int visited[n];
    int weightSum = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    if (head == NULL)
        head = create_node(0, start_vertex, -1);

    while (head != NULL)
    {
        node *temp = head;
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
                if (graph[current][i] != 0)
                {
                    head = insert(head, graph[current][i], i, current);
                }
            }
        }

        visited[current] = 1;
    }

    return weightSum;
}

int main()
{
    int n;
    scanf("%d", &n);

    node *head = NULL;

    int label = 0;
    int graph[n][100];
    int weight;
    int i = 0;
    char c;
    char ch[100];

    while (label < n)
    {
        scanf("%d", &weight);
        graph[label][i++] = weight;
        c = getchar();
        if (c == '\n')
        {
            i = 0;
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
            printf("%d\n", primsAlgo(graph, head, 0, n, 0));
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

            if (startVertex >= n || startVertex < 0)
            {
                printf("-1\n");
                break;
            }

            primsAlgo(graph, head, startVertex, n, 1);
            printf("\n");
            break;
        }

        case 'x':
            return 0;
        }
    }
}