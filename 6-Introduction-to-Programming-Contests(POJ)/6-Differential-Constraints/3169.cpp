#include <stdio.h>
#include <cstring>
#include <queue>
#define MAXN 1010
#define MAXML 10100
#define MAXMD 10100

using namespace std;
const int inf = 0x3f3f3f3f;  

int N, ML, MD;
int edgeCounter = 0;

struct edge{
  int v;
  int w;
  int next;
};

int head[MAXN];
int dis[MAXN];
int vis[MAXN];
int used[MAXN];

edge edges[MAXML + MAXMD + MAXN];

void addEdge(int u, int v, int w){
  edges[edgeCounter].v = v;
  edges[edgeCounter].w = w;
  edges[edgeCounter].next = head[u];
  head[u] = edgeCounter++;
}
void init(){
  edgeCounter = 0;
  memset(dis, 0x3f, sizeof(dis));
  memset(head, 0xff, sizeof(head));
  memset(vis, 0, sizeof(vis));
  memset(used, 0, sizeof(used));
}

int spfa(int s){  
  queue<int> q;  
  dis[s] = 0;  
  vis[s] = 1;
  used[s]++;
  q.push(s);  
  while(!q.empty()){  
    int u = q.front();  
    q.pop();  
    vis[u] = 0;
    for(int i = head[u]; i != -1; i = edges[i].next){  
      int v = edges[i].v;
      int w = edges[i].w;
      if(dis[v] > dis[u] + w){  
          dis[v] = dis[u] + w;
          if(!vis[v]){
            vis[v] = 1;
            q.push(v); 
            used[v]++;
            if(used[v] > N){
              return -1;
            }
          }  
      }  
    }  
  }
  if(dis[N] == inf){
    return -2;
  } 
  return dis[N];
}  

void swap(int &a, int &b){
  int t = b;
  b = a;
  a = t;
}
int main(){
  scanf("%d %d %d", &N, &ML, &MD);
  init();
  int u, v, w;
  for(int i = 0; i < ML; ++i){
    scanf("%d %d %d", &u, &v, &w);
    if(u > v) swap(u, v);
    addEdge(u, v, w);
  }
  for(int i = 0; i < MD; ++i){
    scanf("%d %d %d", &u, &v, &w);
    if(u > v) swap(u, v);
    addEdge(v, u, -w);
  }
  /*for(int i = 1; i < N; ++i){
    addEdge(i + 1, i, -1);
  }*/
  printf("%d\n", spfa(1));
  return 0;
}