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
You are given an integer N representing the number of nodes in the graph . The graph is represented
by adjacency list .The next N lines represent an adjacency list where first integer is node itself and
next integers are the nodes adjacent to it in ascending order . The goal is to implement the following
using a Depth-First Search (DFS) traversal algorithm:
• All path(Node1,Node2): Print all paths from a given source to a destination vertex. Separate each path with a new line , otherwise print -1 if no path exists between nodes.
NOTE - paths are printed in sorted order
• valid tree():This function checks if the given graph is a tree or not. A valid tree has the
following properties:
(a) There are no cycles (loops) in the graph.
(b) Every vertex is reachable from the root vertex.
(c) There are no isolated vertices (vertices not connected to the rest of the graph).
function prints 1 if the given graph is a tree else -1


Input format:
• The first line contains an integer N specifying the number of nodes in the graph.
• Next “N” lines are sequence of integers where first integer is node itself and next integers in
that line are representing nodes which are adjacent to that node.
• Each line of input is a character from the menu list [’a’,’t’,’x’].
• Input ’a’ calls the function All path(Node1,Node2).
• Input ‘t’ calls the function valid tree()
• Input ‘x’ terminates the execution of the program.
• All the inputs in a line are separated by space.


Output format:
• A line may contain -1 or 1.
• The output of the result of any menu is printed in a new line.

*/

int dfs( int** adj, int i, int des, int curr[], int j, int visited[], int n){
    curr[j]=i;
    int k;
    if(i==des){
        for(k=0;k<=j;k++)printf("%d ",curr[k]);
        printf("\n");
        return 1;
    }
    visited[i]=1;
    int val = 0;
    int temp = 0;
    for(k=0;adj[i][k]!=-1;k++){
        if(visited[adj[i][k]]==0){
          temp = dfs(adj,adj[i][k],des,curr,j+1,visited,n);
          if(temp ==1 ) val = temp;
        }
    }
    visited[i]=0;
    return val;
}
void all_paths(int** adj, int src, int des, int n){
    int curr[n];
    memset(curr,-1,sizeof(curr));
    int i,j,k;
    int visited[n];
    memset(visited,0,sizeof(visited));
    int val = dfs(adj, src, des, curr, 0, visited, n);
    if(val==0)printf("-1\n");
    return;
}

int has_Cycle(int**adj, int i,int parent, int visited[], int n){
    visited[i]=1;
    int j,k;
    for(j=0;adj[i][j]!=-1;j++){
        if(adj[i][j]==parent)continue;
        if(visited[adj[i][j]]==1)return 1;
        if(visited[adj[i][j]]==2)continue;
        if(has_Cycle(adj,adj[i][j],i,visited,n)==1)return 1;
    }
    visited[i]=2;
    return 0;
}

void visit(int** adj, int i, int visited[], int n){
    int j,k;
    visited[i]=1;
    for(j=0;adj[i][j]!=-1;j++){
        if(visited[adj[i][j]]==1)continue;
        visit(adj,adj[i][j],visited,n);;
    }
    return;
}
int valid_Tree(int** adj, int n){
    //is top sort possible
    //check1
    int visited[n];
    memset(visited,0,sizeof(visited));
    int i,j,k;
    for(i=0;i<n;i++){
        if(visited[i]==2)continue;
        if(has_Cycle(adj,i,-1,visited,n)==1)return -1;
    }
    //number of connected components is 1
    memset(visited,0,sizeof(visited));
    visit(adj,0,visited,n);
    for(i=0;i<n;i++){
        if(visited[i]==0)return -1;
    }
    return 1;
}
int main(){
    int n,i,j,k,m;
    scanf("%d",&n);
    int** adj = (int**)malloc(1000*sizeof(int*));
    int curr;
    for(i=0;i<1000;i++){
        adj[i]=(int*)malloc(1000*sizeof(int));
        for(j=0;j<1000;j++)adj[i][j]=-1;
    }
    char tlist[1000];
    int d = 0;
    for(i=0;i<n;i++){
        scanf("%d",&curr);
        scanf("%[^\n]s",tlist);
        m = strlen(tlist);
        d = 0;
        k = 0;
        for(j=0;j<m;j++){
            if(tlist[j]==' ')continue;
            d*=10;
            d+=tlist[j]-48;
            if(j==m-1 || tlist[j+1]==' '){
                adj[i][k++]=d;
                d=0;
            }
        }
    }
    //adjacency list constructed
    char s[10];
    int src, des;
    char c;
    scanf("%s",s);
    c = s[0];
    while(c!='x'){
        if(c=='a'){
            scanf("%d %d",&src, &des);
            all_paths(adj,src,des,n);
        }
        else if(c=='t'){
            printf("%d\n",valid_Tree(adj,n));
        }
        scanf("%s",s);
        c = s[0];
    }
    return 1;
}
