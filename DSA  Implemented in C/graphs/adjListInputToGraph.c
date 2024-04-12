#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int m;
    scanf("%d", &m);

    int graph[m][100];

    int label, adj;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label);
        while (scanf("%d", &adj) == 1)
        {
            graph[label][adj] = 1;
            char c = getchar();
            if (c == '\n')
                break;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &label);
        int weight;
        int count = 0;
        while (scanf("%d", &weight) == 1)
        {
            graph[label][count] = weight;
            count++;
            char c = getchar();
            if (c == '\n')
                break;
        }
    }

    printGraph(graph, m);

    return 0;
}
