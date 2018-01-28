#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class Graph{
  typedef pair<int, int> edge;
  public:
    Graph(int v, int e) : V(v), E(e), parent(v + 1) {
      for(int i = 0; i < v + 1; ++i){
        parent[i] = i;
      }
    }
    void addEdge(int u, int v, int w){
      edges.push_back({w, {u, v}});
    }
    int KruskalMST();
  private:
    int find(int u){
      if(u != parent[u]){
        parent[u] = find(parent[u]);
      }
      return parent[u];
    }
    void merge(int u, int v){
      int fu = find(u);
      int fv = find(v);
      parent[fu] = fv;
    }
  private:
    vector<pair<int, edge>> edges;
    int V, E;
    vector<int> parent;
};

int Graph::KruskalMST(){
  int mst_wt = 0;
  sort(edges.begin(), edges.end());
  for(auto i = edges.begin(); i != edges.end(); ++i){
    int u = i->second.first;
    int v = i->second.second;
    int w = i->first;

    int fu = find(u);
    int fv = find(v);
    if(fu != fv){
      mst_wt += w; 
      merge(fu, fv);
    }
  }
  return mst_wt;
}


int main(){
  int V, E;
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  while(scanf("%d %d", &V, &E) == 2){
    Graph G(V, E);
    int u, v, w;
    for(int i = 0; i < E; ++i){
      scanf("%d %d %d", &u, &v, &w);
      G.addEdge(u, v, w);
    }
    printf("%d\n", G.KruskalMST());
  }
  return 0;
}