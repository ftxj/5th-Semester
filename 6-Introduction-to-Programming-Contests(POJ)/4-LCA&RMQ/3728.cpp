/*
  设   lca(u,v) = t
  求   u,v之间的最大利润，可以转化成求
    u,t之间买入卖出，u，t的最大利润，
    t,v之间买入卖出，t，v的最大利润，
    u,t 之间买入，t,v之间卖出，u，t之间的最小买入价格，t，u间的最大卖出价格求差
    使用四个数组记录：up,down,min,max
    则:maxVal(u,v) = max(
      up(u, t), down(t, v), max(t,v) - min(u,t)
    )
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

#define MAXN 50100
#define MAXQ 50100

using namespace std;

int N, Q;

vector<vector<int> > G(MAXN, vector<int>(0));  
vector<vector<int> > Ask(MAXN, vector<int>(0));
vector<vector<int> > Direction(MAXN, vector<int>(0));
vector<bool> Visited(MAXN, false);

vector<int> Ans(MAXQ, -1);

vector<int> fa(MAXN, 0);
vector<int> W(MAXN, 0);

vector<int> dpUp(MAXN, 0);
vector<int> dpDown(MAXN, 0);
vector<int> dpMax(MAXN, 0);
vector<int> dpMin(MAXN, 0);

vector<vector<int> > st(MAXN, vector<int>(0));
vector<vector<int> > ed(MAXN, vector<int>(0));
vector<vector<int> > id(MAXN, vector<int>(0));

int find(int x){
  if(x == fa[x]) return x;
  int oldfa = fa[x];
  fa[x] = find(oldfa);
  dpUp[x] = max(max(dpUp[x], dpUp[oldfa]), dpMax[oldfa] - dpMin[x]);
  dpDown[x] = max(max(dpDown[x], dpDown[oldfa]), dpMax[x] - dpMin[oldfa]);
  dpMax[x] = max(dpMax[x], dpMax[oldfa]);
  dpMin[x] = min(dpMin[x], dpMin[oldfa]);
  return fa[x];
}

void merge(int x, int y){
  int root_x = find(x);  
  int root_y = find(y);  
  fa[root_x] = root_y; 
}

void tarjan(int u){
  Visited[u] = true;  
  for(int i = 0; i < Ask[u].size(); ++i){
    int v = Ask[u][i];
    if(Visited[v] == true){
      int t = find(v);
      int dir = Direction[u][i];
      find(u);
      if(dir > 0){//u -> v
        st[t].push_back(u);
        ed[t].push_back(v);
        id[t].push_back(dir);
      }
      else{ // v -> u
        st[t].push_back(v);
        ed[t].push_back(u);
        id[t].push_back(-dir);
      }
    }
  }
  for(int i = 0; i < G[u].size(); ++i){
    int v = G[u][i];
    if(Visited[v] == false){
      tarjan(v);
      merge(v, u);
    }
  }
  for(int i = 0; i < st[u].size(); i++) {  
    int a = st[u][i];  
    int b = ed[u][i];  
    int t = id[u][i];  
    find(a);  
    find(b);  
    printf("%d, %d, %d, up %d, down %d\n", u, a, b, dpUp[a], dpDown[b]);
    Ans[t] = max(dpUp[a], max(dpDown[b], dpMax[b] - dpMin[a]));  
  }
}


int main(){
  scanf("%d", &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d", &W[i]);
    fa[i] = i;
    dpMax[i] = dpMin[i] = W[i];
    dpUp[i] = dpDown[i] = 0;
  }
  int u, v;
  for(int i = 1; i <= N - 1; ++i){
    scanf("%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  scanf("%d", &Q);
  for(int i = 1; i <= Q; ++i){
    scanf("%d %d", &u, &v);
    Ask[u].push_back(v);
    Ask[v].push_back(u);
    Direction[u].push_back(i);
    Direction[v].push_back(-i);
  }
  tarjan(1);  
  for(int i = 1; i <= Q; ++i){
    printf("%d\n", Ans[i]);
  }
  return 0;
}