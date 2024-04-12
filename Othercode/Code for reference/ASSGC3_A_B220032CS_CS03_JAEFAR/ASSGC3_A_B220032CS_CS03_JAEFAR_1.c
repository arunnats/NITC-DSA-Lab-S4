#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int min(int a, int b)
{
    return (a > b) ? b : a;
}
/*
You are given an undirected graph G. Implement the following functions using DFS as a sub-routine.
(a) noOfConnectedComponents(G): Print the total number of connected components in the graph.
A connected component is a maximal subgraph in which every pair of vertices are connected
by a simple path.
(b) sizeOfComponents(G): Print the sizes of all connected components in the graph, sorted in
increasing order of their sizes. The size of a component is the number of vertices it contains.
(c) noOfBridges(G): Print the number of bridges in the graph. If there are no bridges, print -1. A
bridge is an edge whose removal increases the number of connected components in the graph.
(d) noOfArticulationPoints(G): Print the number of articulation points in the graph. If there are
no articulation points, print -1. An articulation point is a vertex whose removal increases the
number of connected components in the graph

Input format:
• The first line contains an integer (m) specifying the number of nodes in the graph.
• The subsequent next m lines contain the label of the respective node, followed by the nodes
adjacent to it in ascending order of their labels.
• Each line of input is a character from the menu list [’n’,’s’,’b’,’a’,’t’]..
• Input ‘n’ calls the function noOfConnectedComponents(G).
• Input ’s’ calls the function sizeOfComponents(G).
• Input ‘b’ calls the function noOfBridges(G).
• Input ‘a’ calls the function noOfArticulationPoints(G).
• Input ‘t’ terminates the execution of the program.
• All the inputs in a line are separated by space.

Output format:
• A line may contain -1.
• The output of the result of any menu is printed in a new line.

Sample Input 1:
5
1 2
2 1
3 4
4 3 5
5 4
n
s
b
a
t

Sample Output 1:
2
2 3
3
1

*/

int size(int **adj, int i, int n, int visited[])
{
    visited[i] = 1;
    int ans = 1;
    int j;
    for (j = 0; j < n && adj[i][j] != -1; j++)
    {
        if (visited[adj[i][j]] == 1)
            continue;
        ans += size(adj, adj[i][j], n, visited);
    }
    return ans;
}
int num_Connected(int **adj, int n)
{
    int i, j, k;
    int visited[1000];
    memset(visited, 0, sizeof(visited));
    int count = 0;
    for (i = 1; i <= n; i++)
    {
        if (visited[i] == 1)
            continue;
        count++;
        size(adj, i, n, visited);
    }
    return count;
}

void check_Bridges(int **adj, int i, int n, int visited[], int disc[], int low[], int parent, int *count, int *time)
{
    // either use a pointer or a static variable

    visited[i] = 1;

    disc[i] = low[i] = ++(*time);

    // go through all adjacent vertices
    int j, k;
    int a;
    for (j = 0; j < n && adj[i][j] != -1; j++)
    {
        a = adj[i][j];
        // parent case
        if (a == parent)
            continue;
        // visited case
        if (visited[a] == 1)
            low[i] = min(low[i], disc[a]);
        // not visited
        else
        {
            check_Bridges(adj, a, n, visited, disc, low, i, count, time);
            low[i] = min(low[i], low[a]);
            if (low[a] > disc[i])
                (*count)++;
        }
    }
}

int num_Bridges(int **adj, int n)
{
    int visited[1000];
    memset(visited, 0, sizeof(visited));
    int disc[1000];
    memset(disc, -1, sizeof(disc));
    int low[1000];
    memset(low, -1, sizeof(low));
    int parent = -1;
    int i, j, k;
    int count[1] = {0};
    int time[1] = {0};
    for (i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            check_Bridges(adj, i, n, visited, disc, low, parent, count, time);
        }
    }
    return *count;
}

void check_AP(int **adj, int i, int n, int visited[], int disc[], int low[], int *time, int parent, int isAP[])
{
    // count of children in dfs tree
    int children = 0;
    visited[i] = 1;
    disc[i] = low[i] = ++(*time);
    // go through all adjacent vertices
    int a;
    int j;
    for (j = 0; j < n && adj[i][j] != -1; j++)
    {
        a = adj[i][j];
        if (visited[a] == 0)
        {
            children++;
            check_AP(adj, a, n, visited, disc, low, time, i, isAP);
            low[i] = min(low[i], low[a]);
            if (parent != -1 && low[a] >= disc[i])
                isAP[i] = 1;
        }
        else if (a != parent)
        {
            low[i] = min(low[i], disc[a]);
        }
    }
    // if this is the root of the dfs tree and it has more than one child, then why is it an articulation point
    if (parent == -1 && children > 1)
        isAP[i] = 1;
}

int num_AP(int **adj, int n)
{
    int disc[1000];
    memset(disc, 0, sizeof(disc));
    int low[1000];
    int visited[1000];
    memset(visited, 0, sizeof(visited));
    int isAP[1000];
    memset(isAP, 0, sizeof(isAP));
    int time[1] = {0};
    int i;
    int parent = -1;
    for (i = 1; i <= n; i++)
    {
        if (visited[i] == 1)
            continue;
        check_AP(adj, i, n, visited, disc, low, time, parent, isAP);
    }
    int count = 0;
    for (i = 1; i <= n; i++)
    {
        if (isAP[i] == 1)
            count++;
    }
    return count;
}
void size_Connected(int **adj, int n)
{
    int i, j, k;
    int visited[1000];
    memset(visited, 0, sizeof(visited));
    int sizes[1000];
    memset(sizes, 0, sizeof(sizes));
    k = 0;
    for (i = 1; i <= n; i++)
    {
        if (visited[i] == 1)
            continue;
        sizes[k++] = size(adj, i, n, visited);
    }
    for (i = 0; i < n && sizes[i] != 0; i++)
        printf("%d ", sizes[i]);
    printf("\n");
    return;
}

int main()
{
    // input n
    int n, m;
    scanf("%d", &n);
    int i, j, k;
    // construct the adjacency list
    int **adj = (int **)malloc((1000) * sizeof(int *));
    for (i = 1; i <= n; i++)
    {
        adj[i] = (int *)malloc(1000 * sizeof(int));
        for (j = 0; j < n; j++)
            adj[i][j] = -1;
    }
    char tlist[1000];
    char buf[10];
    int d = 0;
    for (i = 1; i <= n; i++)
    {
        scanf("%s", buf);
        scanf("%[^\n]s", tlist);
        m = strlen(tlist);
        d = 0;
        k = 0;
        for (j = 0; j < m; j++)
        {
            if (tlist[j] == ' ')
                continue;
            d *= 10;
            d += tlist[j] - 48;
            if (j == m - 1 || tlist[j + 1] == ' ')
            {
                if (d != i)
                    adj[i][k++] = d;
                d = 0;
            }
        }
    }
    // printing out the adjacency list
    /*for(i=1;i<=n;i++){
        printf("%d ",i);
        for(j=0;adj[i][j]!=-1;j++){
            printf("%d ",adj[i][j]);
        }
        printf("\n");
    }*/
    char s[10];
    char c;
    scanf("%s", s);
    c = s[0];
    int ans;
    while (c != 't')
    {
        if (c == 'n')
        {
            printf("%d\n", num_Connected(adj, n));
        }
        else if (c == 's')
        {
            size_Connected(adj, n);
        }
        else if (c == 'b')
        {
            int ans = num_Bridges(adj, n);
            if (ans == 0)
                printf("\1\n");
            else
                printf("%d\n", ans);
        }
        else if (c == 'a')
        {
            int ans = num_AP(adj, n);
            if (ans == 0)
                printf("-1\n");
            else
                printf("%d\n", ans);
        }
        scanf("%s", s);
        c = s[0];
    }
    return 1;
}
