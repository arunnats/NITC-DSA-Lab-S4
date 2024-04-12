#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

void printPath(int path[], int pathLength)
{
    for (int i = 0; i < pathLength; ++i)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void dfs(int graph[][MAX_NODES], int currentNode, int endNode, bool visited[], int path[], int pathLength)
{
    visited[currentNode] = true;
    path[pathLength++] = currentNode;

    if (currentNode == endNode)
    {
        printPath(path, pathLength);
    }
    else
    {
        for (int i = 0; i < MAX_NODES; ++i)
        {
            if (graph[currentNode][i] != 0 && !visited[i])
            {
                dfs(graph, i, endNode, visited, path, pathLength);
            }
        }
    }

    visited[currentNode] = false; // Backtrack
}

void findAllPaths(int graph[][MAX_NODES], int startNode, int endNode, int numNodes)
{
    bool visited[MAX_NODES] = {false};
    int path[MAX_NODES];
    int pathLength = 0;

    dfs(graph, startNode, endNode, visited, path, pathLength);
}

int main()
{
    int numNodes;
    scanf("%d", &numNodes);

    int graph[MAX_NODES][MAX_NODES] = {0};

    // Read the adjacency matrix
    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < numNodes; ++j)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    int startNode, endNode;
    scanf("%d %d", &startNode, &endNode);

    printf("All paths between nodes %d and %d:\n", startNode, endNode);
    findAllPaths(graph, startNode, endNode, numNodes);

    return 0;
}
