#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#define MAXN 550
#define MAXM 2000
using namespace std;

int fa[MAXN];
int co[MAXN];

int init(){
  memset(co, 0, MAXN * sizeof(int));
  for(int i = 0; i < MAXN; ++i) fa[i] = i;
}

int find(int u){
  if(u == fa[u]) return u;
  int oldp = fa[u];
  fa[u] = find(oldp);
  co[u] = (co[u] + co[oldp]) % 3;
  return fa[u];
}

int merge(int u, int v, int c, int target, int &ff){
  if(u == target || v == target) return 1;
  int pu = find(u);
  int pv = find(v);
  if(pu == pv){
    int oldc = (co[u] + ((2 * co[v]) % 3)) % 3;
    if(oldc == c) return 1;
    ff++; return 0;
  }
  fa[pu] = pv;
  co[pu] = ((c + co[v]) % 3 + ((2 * co[u]) % 3)) % 3;
  return 1;
}

int main(){
  int N, M;
  int u, v, flag, res, flag2, imp;
  char c;
  while(cin >> N >> M){
    imp = 0;
    vector<pair<pair<int, int>,int> > history;    
    for(int i = 0; i < M; ++i){// get input
      cin >> u >> c >> v;
      history.push_back(make_pair(make_pair(u, v),  c == '<'? 1 : (c=='>'? 2 : 0)));
    }
    int ff = 0, confilict = 0, judge = 0, line = 0;
    for(int i = 0; i < N; ++i){
      init(); ff = 0;     
      for(int j = 0; j < M; ++j){
        if(!merge(history[j].first.first, history[j].first.second, history[j].second, i, ff)){
          confilict++; line = max(line, j + 1);
          break;
        }
      }
      if(ff == 0) judge = i;
    }
    if(confilict == N) cout << "Impossible" << endl;
    else if(confilict == N - 1) cout << "Player "<< judge << " can be determined to be the judge after "<< line << " lines" << endl;
    else if(confilict < N - 1) cout << "Can not determine" << endl;
  }
  return 0;
}