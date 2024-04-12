#include <stdio.h>

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

void Floyd_Warshall(int graph[][100], int n)
{

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j] == -1)
                graph[i][j] = 1000;

    for (int via = 0; via < n; via++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (i != via)
                {
                    graph[i][j] = min(graph[i][j], graph[i][via] + graph[via][j]);
                }
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j] == 1000)
                graph[i][j] = -1;
}
int main()
{
    int n;
    scanf("%d", &n);

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

    Floyd_Warshall(graph, n);

    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}