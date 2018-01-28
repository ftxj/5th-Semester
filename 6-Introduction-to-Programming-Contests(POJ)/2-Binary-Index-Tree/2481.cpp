#include <iostream>
#include <cstring>
#include <map>
#include <stack>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAXN 100100
using namespace std;
int N;
struct seg{
  int first;
  int second;
  int index;
  int res;
};
struct cmpB{
  bool operator ()(const seg& a, const seg &b){
    return a.second > b.second || (a.second == b.second && a.first < b.first);
  }
};
struct cmpH{
  bool operator ()(const seg& a, const seg &b){
    return a.index < b.index;
  }
};

int bit[MAXN];

int lowbit(int x) {return x & -x;}
int getSum(int x){
  int res = 0;
  while(x > 0){
    res += bit[x];
    x -= lowbit(x);
  }
  return res;
}

void chVal(int x, int v){
  while(x <= N){
    bit[x] += v;
    x += lowbit(x);
  }
}

void print(vector<seg> &V){
  for(int i = 0; i < V.size(); ++i){
    cout << V[i].first << ","  << V[i].second << " ";
  }
  cout << endl;
}

int main(){
  while(scanf("%d", &N) != EOF && N != 0){
    memset(bit, 0, MAXN * sizeof(int));
    vector<seg> V(N); 
    int u, v;
    for(int i = 0; i < N; ++i){
      scanf("%d %d", &u, &v);
      V[i].first = u + 1;
      V[i].second = v + 1;
      V[i].index = i;
      V[i].res = 0;
    }
    sort(V.begin(), V.end(), cmpB());
    int same = 0;
    seg pre;
    pre.first = V[0].first;
    pre.second = V[0].second;
    V[0].res = 0;
    chVal(V[0].first, 1);

    for(int i = 1; i < V.size(); ++i){
      if(V[i].first == pre.first && V[i].second == pre.second) same++;
      else same = 0;
      V[i].res = getSum(V[i].first) - same;;
      chVal(V[i].first, 1);
      pre.first = V[i].first;
      pre.second = V[i].second;
    }
    sort(V.begin(), V.end(), cmpH());
    for(int i = 0; i < V.size(); ++i){
      printf("%d ", V[i].res);
    }
    printf("\n");
  }
  return 0;
}