#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <cstdio>
#define MAXN 1000
using namespace std;
struct edge{
  int v;
  int w;
  int next;
};
int head[30];
edge edges[2000];
int N, R[30], T[30];

int edgeCounter = 0;
void addEdge(int u, int v, int w){
  edges[edgeCounter].v = v;
  edges[edgeCounter].w = w;
  edges[edgeCounter].next = head[u];
  head[u] = edgeCounter++;
}

int dis[30], used[30], vis[30];
void init(){
  memset(dis, 0x3f, sizeof(dis));
  memset(used, 0, sizeof(used));
  memset(vis, 0, sizeof(vis));
}

int spfa(){
  init();
  queue<int> Q;
  dis[24] = 0;
  vis[24] = 1;
  used[24] = 1;
  Q.push(24);
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for(int i = head[u]; i != -1; i = edges[i].next){
      int v = edges[i].v;
      int w = edges[i].w;
      if(dis[v] > dis[u] + w){
        dis[v] = dis[u] + w;
        if(!vis[v]){
          vis[v] = 1;
          used[v]++;
          if(used[v] > 25) return 1;
          Q.push(v);
        }
      }
    }
  }
  return dis[0];
}
int bsearch(int l, int r){
  int ret = -1;
  int mid;
  while(l <= r){
    mid = (l + r) >> 1;
    memset(head, 0xff, sizeof (head));
    edgeCounter = 0;
    for(int i = 1;i <= 24; ++i){  
      addEdge(i, i - 1, 0);  
      addEdge(i - 1, i, T[i]);  
    }  
    for(int i = 8; i <= 24; ++i){
      addEdge(i, i - 8, -R[i]);
    }
    for (int i = 1; i < 8; ++i) {
      addEdge(i, i - 8 + 24, mid - R[i]);
    }
    addEdge(24, 0, -mid);
    if(spfa() == -mid){
      ret = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  return ret;
}

int main(){
  int Con;
  scanf("%d", &Con);
  while(Con--){
    for(int i = 1; i <= 24; ++i){
      scanf("%d", &R[i]);
    }
    scanf("%d", &N);
    int u;
    for(int i = 1; i <= N; ++i){
      scanf("%d", &u);
      T[u + 1]++;
    }
    int ret = bsearch(0, N);
    if(ret == -1){
      printf("No Solution\n");
    }
    else{
      printf("%d\n", ret);
    }
  }
  return 0;
}