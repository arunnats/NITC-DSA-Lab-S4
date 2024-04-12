#include <stdio.h>
#include <stdlib.h>

struct node
{
    int weight;
    int vertex;
    struct node *next;
};

typedef struct node node;

node *create_node(int weight, int vertex)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->weight = weight;
    newnode->vertex = vertex;
    newnode->next = NULL;

    return newnode;
}

node *insert(node *head, int weight, int vertex)
{

    node *newnode = create_node(weight, vertex);

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

void Dijkstra(node **graph, int *dist, int n, int start_vertex)
{
    node *head = NULL;
    head = insert(head, 0, start_vertex);

    node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        if (temp->weight < dist[temp->vertex])
            dist[temp->vertex] = temp->weight;

        node *trav = graph[temp->vertex];

        while (trav != NULL)
        {
            if (trav->weight + temp->weight < dist[trav->vertex])
                head = insert(head, trav->weight + temp->weight, trav->vertex);
            trav = trav->next;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int i = 1;

    char line[100];
    int ch = 0;
    char c;
    node *graph[n + 1];

    for (int i = 0; i <= n; i++)
        graph[i] = NULL;

    node *temp;

    scanf("%c", &c);
    while (i <= n)
    {
        scanf("%c", &c);

        if (c != '\n')
            line[ch++] = c;

        else
        {
            int result = 0;

            for (int j = 0; j < ch; j++)
            {
                while (j < ch && line[j] != ' ')
                {
                    result = result * 10 + (line[j++] - '0');
                }
                if (result != i)
                {
                    node *newnode = create_node(0, result);

                    if (graph[i] == NULL)
                    {
                        graph[i] = newnode;
                        temp = graph[i];
                    }

                    else
                    {
                        temp->next = newnode;
                        temp = newnode;
                    }
                }
                result = 0;
            }
            i++;
            ch = 0;
        }
    }

    ch = 0;
    i = 1;
    int count;

    while (i <= n)
    {
        scanf("%c", &c);

        if (c != '\n')
            line[ch++] = c;

        else
        {
            int result = 0;
            temp = graph[i];
            count = 0;
            for (int j = 0; j < ch; j++)
            {

                while (j < ch && line[j] != ' ')
                    result = result * 10 + (line[j++] - '0');

                if (count != 0)
                {
                    temp->weight = result;
                    temp = temp->next;
                }

                count++;
                result = 0;
            }
            i++;
            ch = 0;
        }
    }

    int dist[n + 1];
    int start_vertex;

    scanf("%d", &start_vertex);

    for (int i = 0; i <= n; i++)
    {
        dist[i] = 1000;
    }

    Dijkstra(graph, dist, n, start_vertex);

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", dist[i]);
    }
}