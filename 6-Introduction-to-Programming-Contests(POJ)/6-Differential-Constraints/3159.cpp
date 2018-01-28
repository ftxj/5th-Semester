#include <queue>
#include <stdio.h>
#include <vector>
#include <cstring>
#define MAXN 31000 
#define MAXM 151000 
using namespace std;

int N, M;
struct edge{
  int u;
  int v;
  int w;
  int next;
};
typedef pair<int, int> iPair;
struct cmp{
  bool operator() (const iPair &u, const iPair &v){
    return u.second > v.second;
  }
};

int head[MAXN];
edge edges[MAXM];
int dis[MAXN];

void dijkstra(int u){
  memset(dis, 0xff, MAXN * sizeof(int));
  priority_queue<iPair, vector<iPair>, cmp> Q;
  dis[u] = 0;
  Q.push(make_pair(u, 0));
  while(!Q.empty()){
    int u = Q.top().first;
    Q.pop();
    if(u == N) return;
    for(int i = head[u]; i != -1; i = edges[i].next){
      int v = edges[i].v;
      int w = edges[i].w;
      if(dis[u] + w < dis[v] || dis[v] == -1){
        dis[v] = dis[u] + w;
        Q.push(make_pair(v, dis[v]));
      }
    }
  }
}

int main(){
    scanf("%d %d", &N, &M);
    memset(head, 0xff, MAXN * sizeof(int));
    int u, v, w;
    for(int i = 1; i <= M; ++i){
      scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
      edges[i].next = head[edges[i].u];
      head[edges[i].u] = i;
    }
    dijkstra(1);
    printf("%d\n", dis[N]);
  return 0;
}