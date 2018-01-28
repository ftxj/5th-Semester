#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <map>
#include <ctime>
#define MAXM 20
#define MAXT 30
#define MAXN 100
#define MAXP 10000
using namespace std;

int P, N, M, T;
struct link{
  int pre;
  int next;
};

int getIndex(int u, int t, bool isStudent);
void eraseEdge(vector<vector<link> > &Graph, int from, int to);
void addEdge(vector<vector<link> > &Graph, int from, int to);

void PrintGraph(vector<vector<link> > &Graph);

int SPFF(vector<vector<link> > &Graph);
int BFS(vector<vector<link> > &Graph, vector<int> &path);


int DinicDFS(vector<vector<link> > &Graph, vector<int> &level, int s, int t);
int DinicBFS(vector<vector<link> > &Graph, vector<int> &level);
int Dinic(vector<vector<link> > &Graph);

int main(){
#ifdef TEST
  freopen("out.txt", "w", stdout);
  freopen("in.txt", "r", stdin);
#endif
#ifdef TESTSMALL
  freopen("out-small.txt", "w", stdout);
  freopen("in-small.txt", "r", stdin);
#endif
#ifdef TESTBIG
  freopen("out-big.txt", "w", stdout);
  freopen("in-big.txt", "r", stdin);
#endif
  ios_base::sync_with_stdio(false);
  long beginTime = clock();
  while(cin >> P >> N >> M >> T){
    vector<vector<link> > Graph((N + M) * T + 2, vector<link>((N + M) * T + 3, {-1,-1}));
    int u, v, t;
    for(int i = 1; i <= P; ++i){
      cin >> u >> v >> t;
      int stuIndex = getIndex(u,t,true);
      int proIndex = getIndex(v,t,false);
      addEdge(Graph, stuIndex, proIndex);
      addEdge(Graph, 0, stuIndex);
      addEdge(Graph, proIndex, (N + M) * T + 1);
    }

    #ifdef XJDINIC
      cout << Dinic(Graph) << endl;
    #endif

    #ifdef XJSPFF
      cout << SPFF(Graph) << endl;
    #endif
  }
  long endTime = clock();
  cout << "Total time(ms):" << endTime - beginTime << endl;
  return 0;
}

void PrintGraph(vector<vector<link> > &Graph){
  for(int i = 0; i < Graph.size(); ++i){
    int iter = (N + M) * T + 2;
    if(Graph[i][iter].next != -1){
      cout << (i-(i % T? i%T : T))/ T + 1 << "," << (i % T? i%T : T) << ":";
      while(Graph[i][iter].next != -1){
        iter = Graph[i][iter].next;
        cout << (iter-(iter % T? iter%T : T))/ T + 1 << "," << (iter % T? iter%T : T) << "; ";
      }
      cout << endl;
    }
  }
}
int getIndex(int u, int t, bool isStudent){
  if(isStudent) return (u - 1) * T + t;
  return N * T + (u - 1) * T + t;
}
int DinicBFS(vector<vector<link> > &Graph, vector<int> &level){
  queue<int> Q;
  vector<int> Visited((N + M) * T + 2, 0);
  Q.push(0);
  Visited[0] = 1;
  level[0] = 0;
  while(!Q.empty()){
    int top = Q.front();
    Q.pop();
    int iter = (N + M) * T + 2;
    while(Graph[top][iter].next != -1){
      iter = Graph[top][iter].next;
      if(Visited[iter] == 0){
        level[iter] = level[top] + 1;
        Visited[iter] = 1;
        Q.push(iter);
      }
    }
  }
  return level[(M + N) * T + 1] >= 0;  
}
int DinicDFS(vector<vector<link> > &Graph, vector<int> &level, int s, int t){
  if(s == t) return 1;
  int iter = (N + M) * T + 2;
  while(Graph[s][iter].next != -1){
    iter = Graph[s][iter].next;
    if(level[iter] == level[s] + 1){
      int resflow = DinicDFS(Graph, level, iter, t);
      if(resflow == 1){
        eraseEdge(Graph, s, iter);
        addEdge(Graph, iter, s);
        return 1;
      }
    }
  }
  return 0;
}
int Dinic(vector<vector<link> > &Graph){
  int maxflow = 0;
  while(true){
    vector<int> level((N + M) * T + 3, -1); 
    if(DinicBFS(Graph, level)){
      while(int flow = DinicDFS(Graph, level, 0, (M + N) * T + 1))
        maxflow++;
    }
    else return maxflow;
  }
}

int SPFF(vector<vector<link> > &Graph){
  int maxflow = 0;
  vector<int> path;
  while(BFS(Graph, path)){
    maxflow++;
    int pre = path[0];
    for(int i = 1; i < path.size(); ++i){
      eraseEdge(Graph, pre, path[i]);
      addEdge(Graph, path[i], pre);
      pre = path[i];
    }
  }
  return maxflow;
}

int BFS(vector<vector<link> > &Graph, vector<int> &path){
  path.clear();
  queue<int> Q;
  vector<int> Visited((N + M) * T + 2, 0);
  vector<int> Parent((N + M) * T + 2, 0);
  Q.push(0);
  Visited[0] = 1;
  Parent[0] = -1;
  while(!Q.empty()){
    int top = Q.front();
    Q.pop();
    int iter = (N + M) * T + 2;
    while(Graph[top][iter].next != -1){
      iter = Graph[top][iter].next;
      if(Visited[iter] == 0){
        Parent[iter] = top;
        Visited[iter] = 1;
        if(iter == (N + M) * T + 1){
          while(iter != -1){
            path.push_back(iter);
            iter = Parent[iter];
          }
          reverse(path.begin(), path.end());
          return 1;
        }
        Q.push(iter);
      }
    }
  }
  return 0;
}

void eraseEdge(vector<vector<link> > &Graph, int from, int to){
  if(Graph[from][to].next == -1 && Graph[from][to].pre == -1) return;
  int pre = Graph[from][to].pre;
  Graph[from][pre].next = Graph[from][to].next;
  if(Graph[from][to].next != -1)
    Graph[from][Graph[from][to].next].pre = pre;
  Graph[from][to].next = -1;
  Graph[from][to].pre = -1;
}

void addEdge(vector<vector<link> > &Graph, int from, int to){
  if(Graph[from][to].next != -1 || Graph[from][to].pre != -1) return;
  int preFrist = Graph[from][(N + M) * T + 2].next;
  Graph[from][to].next = preFrist;
  Graph[from][to].pre = (N + M) * T + 2;
  if(preFrist != -1)
    Graph[from][preFrist].pre = to;
  Graph[from][(N + M) * T + 2].next = to;
}
