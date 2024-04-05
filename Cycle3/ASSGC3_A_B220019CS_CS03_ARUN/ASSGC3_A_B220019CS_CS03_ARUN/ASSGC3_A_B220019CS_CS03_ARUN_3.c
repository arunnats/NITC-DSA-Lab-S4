#include <stdio.h>
#include <stdlib.h>

int top = -1;
int numberOfPaths = 0;

struct AdjacencyMatrix
{
    int **matrix;
    int rows;
    int cols;
};

void printAdjMatrix(struct AdjacencyMatrix adjMatrix)
{
    for (int i = 0; i < adjMatrix.rows; i++)
    {
        for (int j = 0; j < adjMatrix.cols; j++)
        {
            printf("%d ", adjMatrix.matrix[i][j]);
        }
        printf("\n");
    }
}

int isUndirected(struct AdjacencyMatrix adjMatrix)
{
    for (int i = 0; i < adjMatrix.rows; i++)
    {
        for (int j = 0; j < adjMatrix.cols; j++)
        {
            if (adjMatrix.matrix[i][j] != adjMatrix.matrix[j][i])
                return 0;
        }
    }
    return 1;
}

int isStackNotEmpty(int stack[])
{
    if (top == -1)
        return 0;
    else
        return 1;
}

int pop(int stack[])
{
    int check = isStackNotEmpty(stack);
    if (check == -1)
    {
        return -1;
    }
    else
    {
        int num = stack[top];
        top--;
        return num;
    }
}

void push(int stack[], int data)
{
    top = top + 1;
    stack[top] = data;
    return;
}

int hasCycle(struct AdjacencyMatrix adjMatrix, int visited[], int stack[], int u)
{
    visited[u] = 1;
    push(stack, u);
    while (isStackNotEmpty(stack))
    {
        u = pop(stack);
        for (int v = 0; v < adjMatrix.rows; v++)
        {
            if (adjMatrix.matrix[u][v] == 1)
            {
                if (visited[v] != 1)
                {
                    visited[v] = 1;
                    push(stack, v);
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int isAcyclic(struct AdjacencyMatrix adjMatrix, int visited[], int stack[])
{
    int check;
    for (int u = 0; u < adjMatrix.rows; u++)
    {
        if (visited[u] != 1)
        {
            check = hasCycle(adjMatrix, visited, stack, u);
            if (check == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void dfs(struct AdjacencyMatrix adjMatrix, int u, int visited[], int stack[])
{
    visited[u] = 1;
    for (int v = 0; v < adjMatrix.rows; v++)
    {
        if (adjMatrix.matrix[u][v] == 1 && !visited[v])
        {
            dfs(adjMatrix, v, visited, stack);
        }
    }
    push(stack, u);
}

int isConnected(int visited[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (visited[i] != 1)
            return 0;
    }
    return 1;
}

void dfsForPaths(struct AdjacencyMatrix adjMatrix, int start, int end, int visited[], int stack[])
{
    visited[start] = 1;
    push(stack, start);

    if (start == end)
    {
        for (int i = 0; i <= top; i++)
        {
            printf("%d ", stack[i]);
        }
        numberOfPaths++;
        printf("\n");
    }

    for (int v = 0; v < adjMatrix.rows; v++)
    {
        if (adjMatrix.matrix[start][v] == 1 && !visited[v])
        {
            dfsForPaths(adjMatrix, v, end, visited, stack);
        }
    }

    visited[start] = 0;
    top--;
}

struct AdjacencyMatrix initializeAdjMatrix(int rows, int cols)
{
    struct AdjacencyMatrix adjMatrix;
    adjMatrix.rows = rows;
    adjMatrix.cols = cols;
    adjMatrix.matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        adjMatrix.matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return adjMatrix;
}

int has_cycle_util(struct AdjacencyMatrix adjMatrix, int v, int visited[], int parent)
{
    visited[v] = 1;

    for (int adj_vertex = 0; adj_vertex < adjMatrix.rows; adj_vertex++)
    {
        if (adjMatrix.matrix[v][adj_vertex])
        {
            if (!visited[adj_vertex])
            {
                if (has_cycle_util(adjMatrix, adj_vertex, visited, v))
                    return 1;
            }
            else if (adj_vertex != parent)
            {
                return 1;
            }
        }
    }

    return 0;
}

int has_cycle(struct AdjacencyMatrix adjMatrix)
{
    int *visited = (int *)malloc(adjMatrix.rows * sizeof(int));

    for (int i = 0; i < adjMatrix.rows; i++)
        visited[i] = 0;

    for (int v = 0; v < adjMatrix.rows; v++)
    {
        if (!visited[v])
        {
            if (has_cycle_util(adjMatrix, v, visited, -1))
            {
                free(visited);
                return 1;
            }
        }
    }

    free(visited);
    return 0;
}

void mark_reachable_vertices(struct AdjacencyMatrix adjMatrix, int v, int visited[])
{
    visited[v] = 1;

    for (int adj_vertex = 0; adj_vertex < adjMatrix.rows; adj_vertex++)
    {
        if (adjMatrix.matrix[v][adj_vertex] && !visited[adj_vertex])
            mark_reachable_vertices(adjMatrix, adj_vertex, visited);
    }
}

int is_every_vertex_reachable(struct AdjacencyMatrix adjMatrix, int root)
{
    int *visited = (int *)malloc(adjMatrix.rows * sizeof(int));

    for (int i = 0; i < adjMatrix.rows; i++)
        visited[i] = 0;

    mark_reachable_vertices(adjMatrix, root, visited);

    for (int i = 0; i < adjMatrix.rows; i++)
    {
        if (!visited[i])
        {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

int has_isolated_vertices(struct AdjacencyMatrix adjMatrix)
{
    for (int i = 0; i < adjMatrix.rows; i++)
    {
        int isolated = 1;
        for (int j = 0; j < adjMatrix.cols; j++)
        {
            if (adjMatrix.matrix[i][j])
            {
                isolated = 0;
                break;
            }
        }
        if (isolated)
            return 1;
    }
    return 0;
}

int valid_tree(struct AdjacencyMatrix adjMatrix)
{
    if (has_cycle(adjMatrix))
        return -1;

    if (!is_every_vertex_reachable(adjMatrix, 0))
        return -1;

    if (has_isolated_vertices(adjMatrix))
        return -1;

    return 1;
}

int main()
{
    int num;
    scanf("%d", &num);
    int n = num;

    struct AdjacencyMatrix adjMatrix = initializeAdjMatrix(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjMatrix.matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int node;
        scanf("%d ", &node);
        char c;
        scanf("%c", &c);
        while (c != '\n')
        {
            if (c != ' ')
            {
                int n = c - '0';
                adjMatrix.matrix[node][n] = 1;
            }
            scanf("%c", &c);
        }
    }

    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int stack[n];

    char ans;

    scanf("%c", &ans);

    while (ans != 'x')
    {
        if (ans == 'a')
        {
            int start;
            int end;
            scanf("%d %d", &start, &end);
            for (int i = 0; i < n; i++)
                visited[i] = 0;
            top = -1;
            dfsForPaths(adjMatrix, start, end, visited, stack);
            if (numberOfPaths == 0)
                printf("-1\n");
        }
        else if (ans == 't')
        {
            int result = valid_tree(adjMatrix);
            if (result == 1)
                printf("1\n");
            else
                printf("-1\n");
        }
        scanf("%c", &ans);
    }
    return 0;
}
