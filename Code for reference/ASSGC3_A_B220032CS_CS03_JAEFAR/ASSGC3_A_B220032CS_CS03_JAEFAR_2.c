#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int min(int a,int b){
    return (a>b)?b:a;
}

int max(int a, int b){
    return (a>b)?a:b;
}
/*

Given a directed graph containing N nodes as an adjacency matrix,implement the following using
a Breadth-First Search(BFS) traversal algorithm:
• Is Topological sort possible(): This function checks whether topological sort can be done on
the graph or not. A topological sort is a linear ordering of the vertices in a Directed Acyclic
Graph (DAG) such that for every directed edge e1 − > e2 , vertex e1 appears before e2 in
the ordering. Topological sort is possible if and only if the graph is a DAG.This function will
print 1 if a topological sort is possible, -1 otherwise.
• Number of strongly components(): This function analyzes the graph defined by the edges and
calculates the number of connected components.

Input format:
• The first line contains an integer N specifying the number of nodes in the graph.
• Each line of input is a character from the menu list [’t’,’c’,’x’].
• Input ’t’ calls the function Is Topological sort possible().
• Input ‘c’ calls the function Number of strongly components()
• Input ‘x’ terminates the execution of the program
• All the inputs in a line are separated by space.

Output Format:
• A line may contain -1 or 1.
• The output of the result of any menu is printed in a new line.


Sample Input 1:
6
0 1 1 0 0 0
0 0 1 0 1 0
0 0 0 1 0 1
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
t
c
x
*/
//is top sort possible
//kahns algorithm

int topSort(int** adj, int n){
    int indegree[n];
    int i,j,k;
    memset(indegree, 0, sizeof(indegree));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            indegree[j]+=adj[i][j];
        }
    }
    //queue to store vertices with indegree 0
    int q[10000];
    int head = 0, tail =0;
    for(i=0;i<n;i++){
        if(indegree[i]==0){
            q[tail++]=i;
        }
    }
    int result[n];
    k = -1;
    while(head!=tail){
        int node = q[head];
        head++;
        result[++k]=node;
        for(i=0;i<n;i++){
            if(adj[node][i]==0)continue;
            indegree[i]--;
            if(indegree[i]==0)q[tail++]=i;
        }
    }
    if(k!=n-1)return -1;
    return 1;
}

int dfs(int curr, int des, int** adj, int visited[], int n){
    if(curr==des)return 1;
    visited[curr]=1;
    int i,j;
    for(i=0;i<n;i++){
        if(adj[curr][i]==0)continue;
        //i is an adjacentnode
        if(visited[i]==0){
            if(dfs(i,des,adj,visited,n)==1)return 1;
        }
    }
    return 0;
}
int isPath(int src, int des, int** adj, int n){
    int visited[n];
    memset(visited,0,sizeof(visited));
    return dfs(src,des,adj,visited,n);
}

int num_Scc(int** adj, int n){
    int count = 0;
    int is_scc[n];
    memset(is_scc,0,sizeof(is_scc));
    int i,j,k;
    for(i=0;i<n;i++){
        if(is_scc[i]==0){
            //not any scc, insert it into new scc list
            for(j=i+1;j<n;j++){
                if(is_scc[j]==0 && isPath(i,j,adj, n)==1 && isPath(j,i,adj,n)==1){
                    is_scc[j]=1;
                }
            }
            count++;
        }
    }
    return count;
}

int main(){
    int n;
    scanf("%d",&n);
    int** adj = (int**)malloc(n*sizeof(int*));
    int i,j,k;
    for(i=0;i<n;i++)adj[i]=(int*)malloc(n*sizeof(int));
    //take in adjacency matrix    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)scanf("%d",&adj[i][j]);
    }

    

    char s[10];
    char c;
    scanf("%s",s);
    c = s[0];
    while(c!='x'){
        if(c=='t')printf("%d\n",topSort(adj,n));
        else if(c=='c')printf("%d\n",num_Scc(adj,n));
        scanf("%s",s);
        c = s[0];
    }
    return 1;
}