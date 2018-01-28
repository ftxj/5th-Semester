#include <stdio.h>
#include <vector>
#include <cmath>  
#include <cstring>
#include <iostream>
#define MAXN 100101
#define MAXQ 100101

using namespace std;
struct edge{
  int id;
  int to;
  int from;
  int w;
};

int N, Q;
int currentP;
int dfsOrder = 0;

edge Edges[MAXN + 1];

struct node{
  int id;
  int to; 
  int next;
};

int head[MAXN + 1];
node G[MAXN << 1 + 1];
int Vis[MAXN + 1];

int E[MAXN << 1 + 1];
int L[MAXN << 1 + 1];
int H[MAXN + 1];

int in[MAXN << 1 + 1];
int out[MAXN << 1 + 1];

int M[MAXN << 1 + 1][20];

int BIT[MAXN << 1 + 1];
int Elm[MAXN + 1];
void init(){
  memset(Vis, 0, (MAXN + 1) * sizeof(int));
  memset(Elm, 0, (MAXN + 1) * sizeof(int));
  memset(H, 0, (MAXN + 1) * sizeof(int));
  memset(head, 0xff, (MAXN + 1) * sizeof(int));

  memset(E, 0, (MAXN << 1 + 1) * sizeof(int));
  memset(L, 0, (MAXN << 1 + 1) * sizeof(int));
  memset(in, 0, (MAXN << 1 + 1) * sizeof(int));
  memset(out, 0, (MAXN << 1 + 1) * sizeof(int));
  memset(BIT, 0, (MAXN << 1 + 1) * sizeof(int));

  memset(M, 0, (MAXN << 1 + 1) * 20 * sizeof(int));
}
int etot = 0;
void addEdge(int u,int v,int id){  
  G[etot].to = v;
  G[etot].next = head[u];
  G[etot].id = id;
  head[u] = etot++;
} 

int lowbit(int x) {return x & -x;}
int getsum(int x){
  int sum = 0;
  while(x > 0){
    sum += BIT[x];
    x -= lowbit(x);
  }
  return sum;
}
void addElm(int x, int p){
  while(x <= N << 1){
    BIT[x] += p;
    x += lowbit(x); 
  }
}
int EulerCounter = 0;
void dfs(int u, int fa, int deep){
  Vis[u] = 1;
  E[++EulerCounter] = u;
  L[EulerCounter] = deep;
  if(H[u] == 0) H[u] = EulerCounter;  

  for(int i = head[u]; i != -1; i = G[i].next){
    int v = G[i].to;
    if(Vis[v] == 0){
      int id = G[i].id;

      addElm(++dfsOrder, Edges[id].w);
      in[id] = dfsOrder;
      Elm[v] = dfsOrder;

      dfs(v, id, deep + 1);
      
      addElm(++dfsOrder, -Edges[id].w);
      out[id] = dfsOrder;

      E[++EulerCounter] = u;
      L[EulerCounter] = deep;
    }
  }
}

void InitRMQ(){  
  int i, j;  
  for (i = 0; i < EulerCounter + 1; ++i) M[i][0] = i;  

  for (j = 1; 1 << j <= EulerCounter + 1; ++j){
    for (i = 1; i + (1 << j) - 1 < EulerCounter + 1; ++i){
      if (L[M[i][j - 1]] < L[M[i + (1 << (j - 1))][j - 1]])  
        M[i][j] = M[i][j - 1];  
      else  
        M[i][j] = M[i + (1 << (j - 1))][j - 1];  
    }
  }

}  

int Query(int i, int j){  
    int k;  
    k = int(log(double(j - i + 1))/log(2.0));
    return L[M[i][k]] <= L[M[j - (1 << k) + 1][k]] ? M[i][k] : M[j - (1 << k) + 1][k];  
}  
int Answer(int x, int y){  
  x=H[x]; y=H[y];  
  if(x > y) return E[Query(y, x)];;  
  return E[Query(x, y)];
}  

int main(){
  init();
  scanf("%d %d %d", &N, &Q, &currentP);
  edge temp;
  for(int i = 1; i < N; ++i){
    scanf("%d %d %d", &temp.from, &temp.to, &temp.w);
    temp.id = i;
    Edges[i] = temp;
    addEdge(temp.from, temp.to, i);
    addEdge(temp.to, temp.from, i);
  }
  dfs(1, 0, 0);
  InitRMQ();
  int fun, id, w;
  for(int i = 0; i < Q; ++i){
    scanf("%d", &fun);
    if(fun == 0){
      scanf("%d", &id);
      printf("%d\n", getsum(Elm[currentP]) + getsum(Elm[id]) - 2 * getsum(Elm[Answer(currentP, id)]));
      currentP = id;
    }
    else{
      scanf("%d %d", &id, &w);
      addElm(in[id], w - Edges[id].w);
      addElm(out[id], -w + Edges[id].w);
      Edges[id].w = w;
    }
  }
  return 0;
}