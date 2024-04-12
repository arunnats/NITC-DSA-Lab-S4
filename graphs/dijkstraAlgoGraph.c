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

void printDistances(int dist[], int m)
{

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < m; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], int visited[], int m)
{
    int min = 999, min_index;

    for (int v = 0; v < m; v++)
    {
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int graph[][100], int source, int m)
{
    int dist[m];
    int visited[m];

    for (int i = 0; i < m; i++)
    {
        dist[i] = 999;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < m - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, visited, m);

        // Mark the picked vertex as processed
        visited[u] = 1;

        for (int v = 0; v < m; v++)
        {
            // Update dist[v] only if is not in visited, there is an edge from u to v, and
            // total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != 999 && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printDistances(dist, m);
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
    printf("\n");

    int source;
    printf("Enter the source node: ");
    scanf("%d", &source);

    dijkstra(graph, source, m);

    return 0;
}
