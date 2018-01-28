#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

const int MAXN = 100005;
const int tableAC[3][3] = {
  {0, 1, 2},
  {1, 2, 0},
  {2, 0, 1}
};

const int tableABR[3][3] = {
  {0, 2, 1},
  {1, 0, 2},
  {2, 1, 0}
};

const int tableAB[2][3][3] = {
  {
    {0, 1, 2},
    {2, 0, 1},
    {1, 2, 0}
  },
  {
    {1, 2, 0},
    {0, 1, 2},
    {2, 0, 1}
  }
};

int fa[MAXN];
int rel[MAXN];

void init(){
  for(int i = 0; i < MAXN; ++i){
    fa[i] = i;
  }
  memset(rel, 0, MAXN * sizeof(int));
}

int find(int u){
  if(u == fa[u]){
    return u;
  }
  else{
    int prefa = fa[u];
    fa[u] = find(fa[u]);
    rel[u] = tableAC[rel[u]][rel[prefa]];
    return fa[u];
  }
}

void merge(int r, int u, int v){
  int fau = find(u);
  int fav = find(v);
  fa[fau] = fa[fav];
  rel[fau] = tableAB[r][rel[u]][rel[v]];
}

int check(int r, int u, int v){
  int fau = find(u);
  int fav = find(v);
  if(fau != fav) return true;
  return tableABR[rel[u]][rel[v]] == r;
}

int main(){
  int N, K, D, X, Y, res = 0;
  init();
  scanf("%d %d", &N, &K);
  for(int i = 0; i < K; ++i){
      scanf("%d %d %d", &D, &X, &Y);
      if(X <= N && Y <= N && check(D - 1, X, Y)){
        merge(D - 1, X, Y);
      }
      else{
        res++;
      }
  }
  printf("%d", res);
  return 0;
}