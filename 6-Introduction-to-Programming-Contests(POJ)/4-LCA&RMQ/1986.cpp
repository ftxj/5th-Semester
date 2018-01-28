#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#define MAXN 40100
#define MAXE 40100
using namespace std;

int N, E, Q;

struct edge{
  int to;
  int w;
};


vector<vector<edge> > G(MAXN, vector<edge>(0));

vector<vector<int> > Ask(MAXN, vector<int>(0));
vector<vector<int> > Index(MAXN, vector<int>(0));
vector<int> father(MAXN, 0);

vector<int> Ans(MAXN, 0);
vector<int> Vis(MAXN, 0);

vector<int> fa(MAXN, 0);
vector<int> dis(MAXN, 0);

vector<vector<int> > st(MAXN, vector<int>(0));
vector<vector<int> > ed(MAXN, vector<int>(0));
vector<vector<int> > id(MAXN, vector<int>(0));

int find(int x){
  if(x == fa[x]) return x;
  int oldfa = fa[x];
  fa[x] = find(oldfa);
  dis[x] = dis[oldfa] + dis[x];
  return fa[x];
}

void tarjan(int u){
  Vis[u] = 1;
  for(int i = 0; i < Ask[u].size(); ++i){
    int v = Ask[u][i];
    int index = Index[u][i];
    if(Vis[v] == 1){
      int t = find(v);
      st[t].push_back(u);
      ed[t].push_back(v);
      id[t].push_back(Index[u][i]);
    }
  }
  for(int i = 0; i < G[u].size(); ++i){
    int v = G[u][i].to;
    if(Vis[v] == 0){
      tarjan(v);
      fa[v] = u;
      dis[v] = G[u][i].w;
    }
  }
  for(int i = 0; i < st[u].size(); ++i){
    find(st[u][i]);
    find(ed[u][i]);
    Ans[id[u][i]] = dis[st[u][i]] + dis[ed[u][i]];
  }
}

int main(){  
    scanf("%d %d", &N, &E);  
    //if(N != E + 1) printf("?");
    int u, v, w;
    char d;
    for(int i = 1; i <= E; ++i){
      scanf("%d %d %d %c", &u, &v, &w, &d);
      edge temp;
      temp.to = v;
      temp.w = w;
      G[u].push_back(temp);
      temp.to = u;
      G[v].push_back(temp);
    }
    for(int i = 1; i <= N; ++i){
      fa[i] = i;
    }
    scanf("%d", &Q);
    for(int i = 1; i <= Q; ++i)  {  
        scanf("%d %d", &u, &v);  
        Ask[u].push_back(v);
        Ask[v].push_back(u);
        Index[u].push_back(i);
        Index[v].push_back(i);
    }

    tarjan(1);

    for(int i = 1; i <= Q; ++i){
      printf("%d\n", Ans[i]);
    }
  return 0;  
}  