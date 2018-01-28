#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int N, Q;

int find(int x, vector<int>& fa){
  if(x == fa[x]) return x;
  int oldfa = fa[x];
  fa[x] = find(oldfa, fa);
  return fa[x];
}

void merge(int x, int y, vector<int>& fa){
  int root_x = find(x, fa);  
  int root_y = find(y, fa);  
  fa[root_x] = root_y; 
}

void tarjan(int u, vector<int>& fa, vector<vector<int> >& Index, vector<vector<int> >& G, vector<vector<int> >& Ask, vector<int>& Ans, vector<int>& Vis){
  Vis[u] = 1;  
  for(int i = 0; i < Ask[u].size(); ++i){
    int v = Ask[u][i];
    if(Vis[v] == 1){
      int t = find(v, fa);
      Ans[t]++;
    }
  }
  for(int i = 0; i < G[u].size(); ++i){
    int v = G[u][i];
    if(Vis[v] == 0){
      tarjan(v, fa,Index, G, Ask, Ans, Vis);
      merge(v, u, fa);
    }
  }
}

int main(){  
  while(scanf("%d", &N) != EOF){  
    vector<int> father(N + 1, -1);
    vector<vector<int> > G(N + 1, vector<int>(0));
    vector<int> Ans(N + 1, 0);
    vector<int> Vis(N + 1, 0);
    vector<int> fa(N + 1, 0);
    int u, v, m;
    for(int i = 1; i <= N; ++i){  
      fa[i] = i;
      scanf("%d:(%d)", &u, &m);  
      for(int j = 0; j < m; j++){  
          scanf("%d", &v);  
          G[u].push_back(v);
          father[v] = u;
      }  
    }  
    scanf("%d", &Q); 
    vector<vector<int> > Ask(N + 1, vector<int>(0));
    vector<vector<int> > Index(N + 1, vector<int>(0));
    for(int i = 1; i <= Q; ++i)  {  
        while(getchar() != '(');
        scanf("%d %d)", &u, &v); 
        Ask[u].push_back(v);
        Ask[v].push_back(u);
    }
    int root;
    int i = N;
    while(father[i] != -1){
      i = father[i];
    }
    root = i;

    tarjan(root, fa,Index, G, Ask, Ans, Vis);
    
    for(int i = 1; i <= N; ++i){
      if(Ans[i] > 0){
        printf("%d:%d\n", i, Ans[i]);
      }
    }
  } 
  return 0;  
}  