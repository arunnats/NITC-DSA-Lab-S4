#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top = -1;

void print_adj_matrix(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int stack_not_empty(int stack[])
{
    if(top==-1)
        return 0;
    else
        return 1;
}
int pop(int stack[])
{
    int check = stack_not_empty(stack);
    if (check==-1)
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
void push(int stack[] , int data)
{
    top = top+1;
    stack[top] = data;
    return;
}

int cycle_check(int **adj_matrix , int visited[], int stack[],int n,int u)
{
    visited[u] = 1;
    push(stack,u);
    while(stack_not_empty(stack))
    {
        u = pop(stack);
        for(int v =0;v<n;v++)
        {
            if(adj_matrix[u][v]==1)
            {
                if(visited[v]!=1)
                {
                    visited[v]=1;
                    push(stack,v);
                }
                else
                {
                    for(int i =0;i<n;i++)
                    {
                        if(stack[i]==v)
                            return 0;  //cycle found
                    }
                    //printf("%d %d",u,v);
                    
                }
                    
            }
        }
    }
    //push(stack,u);
    return 1; //no cycle found
}

int cyclic(int **adj_matrix , int visited[], int stack[],int n)
{
    int check;
    for(int u = 0;u<n;u++)
    {
        if(visited[u]!=1)
        {
            check = cycle_check(adj_matrix,visited,stack,n,u);
            if(check==0)  //cycle is found
            {
                //printf("%d\n",u);
                return 0;
            }     
        }   
    }
    return 1; //no cycle found
}

void dfs(int **adj_matrix, int n, int u,int visited[],int stack[]) {
    visited[u] = 1; // Mark current vertex as visited
    //printf("%d ", u); // Print the current vertex

    // Visit all adjacent vertices of vertex u
    for (int v = 0; v < n; v++) {
        if (adj_matrix[u][v] == 1 && !visited[v]) {
            dfs(adj_matrix, n, v,visited,stack); // Recursive call to DFS for adjacent unvisited vertex
        }
    }
    push(stack,u);

}

void dfs_without_stack(int **adj_matrix, int n, int u,int visited[]) {
    visited[u] = 1; // Mark current vertex as visited
    //printf("%d ", u); // Print the current vertex

    // Visit all adjacent vertices of vertex u
    for (int v = 0; v < n; v++) {
        if (adj_matrix[u][v] == 1 && !visited[v]) {
            dfs_without_stack(adj_matrix, n, v,visited); // Recursive call to DFS for adjacent unvisited vertex
        }
    }

}

int main()
{
    int num;
    scanf("%d",&num);
    int n = num;
    int rows = n;
    int cols = n;

    int **adj_matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        adj_matrix[i] = (int *)malloc(cols * sizeof(int));
    }


    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
            scanf("%d",&adj_matrix[i][j]);
    }

    getchar();

    int visited[n];
    for(int i =0;i<n;i++)
        visited[i] = 0;
    
    int stack[n];

    char ans;

    /* 
    t - checks if topological sorting is possible i.e checks if the graph is acyclic
    c - counts the number of strongly connected components
    x - terminates
    */

   scanf("%c",&ans);

   while(ans!='x')
   {
        if(ans=='t')
        {
            int check;
            check = cyclic(adj_matrix,visited,stack,n);

            if(check==1)
                //printf("no cycle found\n");
                printf("1\n");
            else
                //printf("cycle found\n");
                printf("-1\n");
        }

        else if(ans=='c')
        {   
            for(int i =0;i<n;i++)
                visited[i] = 0;
            
            top = -1;

            for (int i = 0; i < n; i++) 
            {
                if (!visited[i]) 
                {
                    dfs(adj_matrix, n, i,visited,stack);
                }
            }
            int **adj_matrix_T = (int **)malloc(cols * sizeof(int *));
            for (int i = 0; i < cols; i++) 
            {
                adj_matrix_T[i] = (int *)malloc(rows * sizeof(int));
            }
            for(int i = 0;i<n;i++)
            {
                for(int j = 0;j<n;j++)
                    adj_matrix_T[i][j] = adj_matrix[j][i];
            }

            int scc = 0;
            for(int i =0;i<n;i++)
                visited[i] = 0;
    
            while(stack_not_empty(stack))
            {
                int u = pop(stack);
                if(visited[u]!=1)
                {
                    scc++;
                    dfs_without_stack(adj_matrix_T,n,u,visited);
                }
            }

            printf("%d\n",scc);
        }
        scanf("%c",&ans);
   }
    return 0;
   }
