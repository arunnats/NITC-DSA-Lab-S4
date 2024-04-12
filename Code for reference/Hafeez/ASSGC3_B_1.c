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

void sequence(int graph[][100], node *head, int start_vertex, int *MSP_sum, int n, int print_weight, int print_seq)
{

    int visited[n];

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
                if (print_seq)
                    printf("%d %d ", temp->parent, temp->vertex);
                if (print_weight)
                    *MSP_sum = *MSP_sum + temp->weight;
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

    int MSP_sum = 0;
    while (1)
    {
        scanf("%c", &c);
        switch (c)
        {
        case 't':
        {
            sequence(graph, head, 0, &MSP_sum, n, 1, 0);
            printf("%d\n", MSP_sum);
            break;
        }

        case 's':
        {
            int result = 0;
            while (c != ')')
            {
                scanf("%c", &c);
                if (c != '(' && c != ')')
                {
                    result = result * 10 + (c - '0');
                }
            }
            sequence(graph, head, result, &MSP_sum, n, 0, 1);
            printf("\n");
            break;
        }

        case 'x':
            return 0;
        }
    }
}