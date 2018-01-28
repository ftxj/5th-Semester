#include <stdio.h>
#include <cstring>
#define MAXN 51000
#define inf 0x3f3f3f3f
using namespace std;
struct edge{
  int v;
  int w;
  int next;
};

int N;
int head[MAXN];

edge edges[MAXN << 2];
int Q[MAXN << 4];

int IntervalMax = 0;
int edgeCounter = 0;

int dis[MAXN];  
int vis[MAXN]; 


void init(){
  IntervalMax = 0;
  edgeCounter = 0;
  memset(vis, 0, MAXN * sizeof(int));
  memset(head, 0xff, MAXN * sizeof(int));
}
void spfa(){  
  int qhead = 0, qtail = 1;  
  for (int i = 0; i <= IntervalMax; ++i){  
      dis[i] = -inf;  
  }  
  Q[qhead] = 0;  
  dis[0] = 0;  
  while (qhead < qtail){  
    int u = Q[qhead];  
    vis[u] = 1;  
    for (int p = head[u]; p != -1; p = edges[p].next){  
        int v = edges[p].v;  
        int w = edges[p].w;
        if (dis[v] < dis[u] + w){  
            dis[v] = dis[u] + edges[p].w;  
            if (!vis[v]){  
                vis[v] = 1;  
                Q[qtail++] = v;  
            }  
        }  
    }  
    vis[u] = 0;  
    qhead++;  
  }  
}  

void addEdge(int u, int v, int w){
  edges[edgeCounter].v = v;
  edges[edgeCounter].w = w;
  edges[edgeCounter].next = head[u];
  head[u] = edgeCounter++;
}
int main(){
  int u, v, w;
  while(scanf("%d", &N) == 1){
    init();
    for(int i = 1; i <= N; ++i){
      scanf("%d %d %d", &u, &v, &w);
      u++; v++;
      if(v > IntervalMax) IntervalMax = v;
      addEdge(u - 1, v, w);
    }
    for(int i = 0; i <= IntervalMax; ++i){
      addEdge(i, i + 1, 0);
      addEdge(i + 1, i, -1);
    }
    spfa();
    printf("%d\n", dis[IntervalMax]);
  }
  return 0;
}