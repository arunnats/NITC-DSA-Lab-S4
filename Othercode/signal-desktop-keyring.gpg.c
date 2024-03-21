#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top = -1;
int no_of_paths = 0;

void print_adj_matrix(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int undirected_check(int **adj_matrix, int n)  //adjacency matrix of an undirected graph is symmetric
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            if(adj_matrix[i][j]!=adj_matrix[j][i])
                return 0;
        }
    }
    return 1 ;  //return 1 if it is undirected   
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
                    return 0;  //cycle found
                }
            }
        }
    }
    return 1; //no cycle found
}

int acyclic_check(int **adj_matrix , int visited[], int stack[],int n)
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

int connectedness_check(int visited[],int n)
{
    for(int i =0;i<n;i++)
    {
        if (visited[i]!=1)
            return 0;   //not connected
    }
    return 1;
}

void dfs_for_path(int **adj_matrix, int n, int start,int end,int visited[],int stack[]) {
    visited[start] = 1; // Mark current vertex as visited
    push(stack,start);

    if(start==end){
        for (int i = 0; i <=top; i++) {
        printf("%d ", stack[i]); // Print path (add 1 to convert to 1-based indexing)
    }
    no_of_paths++;
    printf("\n");
    }

    for (int v = 0; v < n; v++) 

    {
        if (adj_matrix[start][v] == 1 && !visited[v]) 
        {
            dfs_for_path(adj_matrix, n, v,end,visited,stack); // Recursive call to DFS for adjacent unvisited vertex
        }
    }
    // if(visited[end]==1)
    // {
    //     for(int i = 0;i<n;i++)
    // {
    //     if(visited[i]==1)
    //         printf("%d ",i);
    // }
    // printf("\n");
    // }

    visited[start] = 0;
    top--;
    
}

// int main()
// {
//     int num;
//     scanf("%d",&num);
//     int n = num;
//     int rows = n;
//     int cols = n;

//     int **adj_matrix = (int **)malloc(rows * sizeof(int *));
//     for (int i = 0; i < rows; i++) {
//         adj_matrix[i] = (int *)malloc(cols * sizeof(int));
//     }

//     for(int i =0;i<n;i++)
//     {
//         for (int j = 0; j<n; j++)
//         {
//            adj_matrix[i][j] = 0;
//         }
//     }
       
        
//     for(int i = 0;i<n;i++)
//     {
//         int node;
//         scanf("%d ",&node);
//         char c;
//         scanf("%c",&c);
//         while(c!='\n')
//         {
//             if(c!=' ')
//             {
//                 int n = c -'0';
//                 adj_matrix[node][n] = 1;
//             }
//             scanf("%c",&c);
//         }
//     }
    
//     int flag_undirected;
//     flag_undirected = undirected_check(adj_matrix,n);

//     printf("%d\n",flag_undirected);

//     int visited[n];
//     for(int i =0;i<n;i++)
//         visited[i] = 0;
    
//     int stack[n];


//     int flag_acyclic;
//     flag_acyclic = acyclic_check(adj_matrix,visited,stack,n);
//     printf("%d\n",flag_acyclic);

//     for(int i =0;i<n;i++)
//         visited[i] = 0;
    
//     dfs(adj_matrix,n,0,visited,stack);
//     int flag_connected;
//     flag_connected = connectedness_check(visited,n);
//     printf("%d\n",flag_connected);

//     int start;
//     int end;

//     scanf("%d %d",&start,&end);

//     dfs_for_path(adj_matrix,n,start,end,visited,stack);

//     if(no_of_paths==0)
//         printf("-1\n");


//     return 0;

// }

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

    for(int i =0;i<n;i++)
    {
        for (int j = 0; j<n; j++)
        {
           adj_matrix[i][j] = 0;
        }
    }
       
        
    for(int i = 0;i<n;i++)
    {
        int node;
        scanf("%d ",&node);
        char c;
        scanf("%c",&c);
        while(c!='\n')
        {
            if(c!=' ')
            {
                int n = c -'0';
                adj_matrix[node][n] = 1;
            }
            scanf("%c",&c);
        }
    }
    
    int visited[n];
    for(int i =0;i<n;i++)
        visited[i] = 0;
    
    int stack[n];

    char ans;

    /* 
    a - prints all possible paths between two nodes; -1 if no path exists
    t - checks if the graph is a valid tree
    x - terminates
    */

   scanf("%c",&ans);

   while(ans!='x')
   {
        if(ans=='a')
        {
            int start;
            int end;
            scanf("%d %d",&start,&end);
            for(int i =0;i<n;i++)
                visited[i] = 0;
            top = -1;
            dfs_for_path(adj_matrix,n,start,end,visited,stack);
            if(no_of_paths==0)
                printf("-1\n");
        }

        else if(ans=='t')
        {   
            int flag_undirected;
            flag_undirected = undirected_check(adj_matrix,n);

            for(int i =0;i<n;i++)
                visited[i] = 0;
            top = -1;
            int flag_acyclic;
            flag_acyclic = acyclic_check(adj_matrix,visited,stack,n);
            for(int i =0;i<n;i++)
                visited[i] = 0;
            top = -1;
            dfs(adj_matrix,n,0,visited,stack);
            int flag_connected;
            flag_connected = connectedness_check(visited,n);

            if(flag_acyclic && flag_connected && flag_undirected)
                printf("1\n");
            else
                printf("-1\n");
            //printf("%d %d %d",flag_acyclic,flag_connected,flag_undirected);
        }
        scanf("%c",&ans);
    }
    return 0;

}