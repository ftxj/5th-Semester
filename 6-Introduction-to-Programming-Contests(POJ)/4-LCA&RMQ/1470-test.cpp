#include <stdio.h>  
#include <string.h>  
#include <algorithm>
#include <vector>  
#include <iostream>
#define MAX 1000  
using namespace std;  
vector <int> v[MAX];  
vector <int> q[MAX];  
int degree[MAX];  
bool vis[MAX];  
int cnt[MAX];  
int bin[MAX];  
  
int find(int x)  
{  
    if(x != bin[x])  
        return bin[x] = find(bin[x]);  
    return bin[x];  
}  
void dfs(int u)  
{  
    bin[u] = u;  
    int len = v[u].size(),i = 0;  
    for(i = 0;i < len; i++)  
    {  
        dfs(v[u][i]);  
        bin[v[u][i]] = u;  
    }  
    vis[u] = true;  
    len = q[u].size();  
    for(i = 0;i < len; i++)  
    {  
        if(vis[q[u][i]]){  
            cnt[find(q[u][i])]++;  
            printf("%d,%d,%d\n",u, q[u][i], find(q[u][i]));
        }
    }  
}  
int main()  
{  int N;
    char s1[10],s2[10],s3[10];  
    int n,m,i,j,k,x,y;  
    int *Data ,**RMQ, *D;
    int Index_min;

    for (i = 0; i < N; i++){
        for (j = i + 1; j < N; j++){ 
            RMQ[i][j] = Data[RMQ[i][j - 1]] < Data[j] ? RMQ[i][j - 1] : j; 
        }
    }


    for (j = 1; 1 << j <= N + 1; ++j){
        for (i = 1; i + (1 << j) - 1 < N + 1; ++i){
            if (Data[RMQ[i][j - 1]] < Data[RMQ[i + (1 << (j - 1))][j - 1]])  
                RMQ[i][j] = RMQ[i][j - 1];  
            else  
                RMQ[i][j] = RMQ[i + (1 << (j - 1))][j - 1];  
        }
    }


    return 0;  
}  
