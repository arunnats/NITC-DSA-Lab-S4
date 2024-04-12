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

int find_parent(int vertex, int *parent)
{
    if (vertex == parent[vertex])
        return vertex;

    return parent[vertex] = find_parent(parent[vertex], parent);
}

void union_size(int *parent, int *size, node *node)
{
    int u = node->parent;
    int v = node->vertex;
    int parent_u = find_parent(u, parent);
    int parent_v = find_parent(v, parent);

    if (size[parent_u] > size[parent_v])
    {
        parent[parent_v] = parent_u;
        size[parent_u] = size[parent_u] + size[parent_v];
    }
    else
    {
        parent[parent_u] = parent_v;
        size[parent_v] = size[parent_u] + size[parent_v];
    }
}

int MSP(int graph[][100], int n)
{
    int parent[n];
    int size[n];
    int MSP_size = 0;

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }

    node *head = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (graph[i][j] != 0)
                head = insert(head, graph[i][j], j, i);
    }

    node *temp = head;

    while (temp != NULL)
    {
        if (find_parent(temp->vertex, parent) != find_parent(temp->parent, parent))
        {
            MSP_size += temp->weight;
            union_size(parent, size, temp);
        }

        temp = temp->next;
    }

    return MSP_size;
}

int main()
{
    int n;
    scanf("%d", &n);

    int i = 0;

    char line[100];
    int ch = 0;
    char c;
    int graph[n][100];

    scanf("%c", &c);
    while (i < n)
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
                    result = result * 10 + (line[j++] - '0');
                if (result != i)
                    graph[i][result] = 1;
                result = 0;
            }
            i++;
            ch = 0;
        }
    }

    ch = 0;
    i = 0;

    while (i < n)
    {
        scanf("%c", &c);

        if (c != '\n')
            line[ch++] = c;

        else
        {
            int result = 0;
            int index = 0;
            int count = 0;
            for (int j = 0; j < ch; j++)
            {

                while (graph[i][index] != 1)
                    index++;

                while (j < ch && line[j] != ' ')
                    result = result * 10 + (line[j++] - '0');

                if (count != 0)
                    graph[i][index++] = result;

                count++;
                result = 0;
            }
            i++;
            ch = 0;
        }
    }

    printf("%d", MSP(graph, n));
}