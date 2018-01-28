#include <iostream>
#include <cstring>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
uint32_t sigema[65];
uint32_t alpha[65][65];
uint32_t s1[10001], s2[10001];
uint32_t m, n1, n2;

class ArrayGraph{
  struct edges{
    edges(): has(vector<bool>(3, false)) {}
    uint32_t to[3];
    uint32_t weight[3];
    vector<bool> has;
  };
  
  struct compare{
    bool operator()(const pair<uint32_t, uint32_t>& l, const pair<uint32_t, uint32_t>& r) {  
       return l.second > r.second;  
    }  
  };

public:
  vector<edges> E;
  int n;
  ArrayGraph(uint32_t N) : n(N),
    E(vector<edges>(N)){}
  ~ArrayGraph(){}

  void addEdges(uint32_t i, uint32_t j){
    uint32_t u = i * (n2 + 1) + j;

    uint32_t left = u + 1;
    uint32_t down = (i + 1) * (n2 + 1) + j;
    uint32_t oblique = (i + 1) * (n2 + 1) + j + 1;
    
    if(j < n2)
      insertEdge(u, left, 0, sigema[s2[j + 1]]);
    if(i < n1)
      insertEdge(u, down, 1, sigema[s1[i + 1]]);
    if(i < n1 && j < n2)
      insertEdge(u, oblique, 2, alpha[s1[i + 1]][s2[j + 1]]);
  }
  
  void insertEdge(uint32_t u, uint32_t v, uint32_t id, uint32_t weight){
    E[u].to[id] = v;
    E[u].weight[id] = weight;
    E[u].has[id] = true;
  }

  uint32_t getMinW(){
    return dijkstra(0, n1 * (n2 + 1) + n2);
  }

  uint32_t dijkstra(uint32_t source, uint32_t target){
    priority_queue<pair<uint32_t, uint32_t>, vector<pair<uint32_t, uint32_t>>, compare> Q;
    vector<uint32_t> dist(n, UINT32_MAX);
    vector<bool> visisted(n, false);
    dist[source] = 0;
    Q.push(make_pair(source, 0));

    while(!Q.empty()){
      auto u = Q.top();
      Q.pop();
      if(visisted[u.first] == true){
        continue;
      }
      visisted[u.first] = true;
      for(int i = 0; i < 3; ++i){
        if(E[u.first].has[i] == false){
          continue;
        }
        uint32_t v =  E[u.first].to[i];
        uint32_t w =  E[u.first].weight[i];
        uint32_t alt = dist[u.first] + w;
        if(alt < dist[v]){
          dist[v] = alt;
          Q.push(make_pair(v, dist[v]));
        }
      }
    }
    return dist[target];
  }

};
int main(){
  while(std::cin >> m){
    for(uint32_t i = 0; i < m; ++i){
      std::cin >> sigema[i];
    }
    
    for(uint32_t i = 0; i < m; ++i){
      for(uint32_t j = 0; j < m; ++j){
        std::cin >> alpha[i][j];
      }
    }

    std::cin >> n1;
    for(uint32_t i = 1; i <= n1; ++i){
      std::cin >> s1[i];
    }

    std::cin >> n2;
    for(uint32_t i = 1; i <= n2; ++i){
      std::cin >> s2[i];
    }

    ArrayGraph G((n1 + 1)* (n2 + 1));
    for(int i = 0; i <= n1; ++i){
      for(int j = 0; j <= n2; ++j){
        G.addEdges(i, j);
      }
    }
    cout << G.getMinW() << endl;
  }
  return 0;
}