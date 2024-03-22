#include <stdio.h>
#include <stdlib.h>

int top = -1;

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

int stackNotEmpty(int stack[])
{
    if (top == -1)
        return 0;
    else
        return 1;
}

int pop(int stack[])
{
    int check = stackNotEmpty(stack);
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

int cycleCheck(struct AdjacencyMatrix adjMatrix, int visited[], int stack[], int u)
{
    visited[u] = 1;
    push(stack, u);
    while (stackNotEmpty(stack))
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
                    for (int i = 0; i < adjMatrix.rows; i++)
                    {
                        if (stack[i] == v)
                            return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int cyclic(struct AdjacencyMatrix adjMatrix, int visited[], int stack[])
{
    int check;
    for (int u = 0; u < adjMatrix.rows; u++)
    {
        if (visited[u] != 1)
        {
            check = cycleCheck(adjMatrix, visited, stack, u);
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

void dfsWithoutStack(struct AdjacencyMatrix adjMatrix, int u, int visited[])
{
    visited[u] = 1;
    for (int v = 0; v < adjMatrix.rows; v++)
    {
        if (adjMatrix.matrix[u][v] == 1 && !visited[v])
        {
            dfsWithoutStack(adjMatrix, v, visited);
        }
    }
}

struct AdjacencyMatrix allocateAdjMatrix(int rows, int cols)
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

int main()
{
    int num;
    scanf("%d", &num);
    int n = num;

    struct AdjacencyMatrix adjMatrix = allocateAdjMatrix(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMatrix.matrix[i][j]);
    }

    getchar();

    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int stack[n];

    char ans;

    scanf("%c", &ans);

    while (ans != 'x')
    {
        if (ans == 't')
        {
            int check;
            check = cyclic(adjMatrix, visited, stack);

            if (check == 1)
                printf("1\n");
            else
                printf("-1\n");
        }

        else if (ans == 'c')
        {
            for (int i = 0; i < n; i++)
                visited[i] = 0;

            top = -1;

            for (int i = 0; i < n; i++)
            {
                if (!visited[i])
                {
                    dfs(adjMatrix, i, visited, stack);
                }
            }
            struct AdjacencyMatrix adjMatrixT = allocateAdjMatrix(adjMatrix.cols, adjMatrix.rows);
            for (int i = 0; i < adjMatrix.rows; i++)
            {
                for (int j = 0; j < adjMatrix.cols; j++)
                    adjMatrixT.matrix[j][i] = adjMatrix.matrix[i][j];
            }

            int scc = 0;
            for (int i = 0; i < n; i++)
                visited[i] = 0;

            while (stackNotEmpty(stack))
            {
                int u = pop(stack);
                if (visited[u] != 1)
                {
                    scc++;
                    dfsWithoutStack(adjMatrixT, u, visited);
                }
            }

            printf("%d\n", scc);
        }
        scanf("%c", &ans);
    }

    for (int i = 0; i < adjMatrix.rows; i++)
    {
        free(adjMatrix.matrix[i]);
    }
    free(adjMatrix.matrix);

    return 0;
}
