#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
#define MAXN 110005
#define MAXM 110005

int N, M;
int bit[MAXN];
int S[MAXN];
int flag = 0;
int counter = 1;
vector<vector<int> >Children(MAXN);

int dfsNum[MAXN];
int newphe[MAXN];

void dfs(int source){
  newphe[source] = counter;
  for(int i = 0; i < Children[source].size(); ++i){
    counter++;
    dfs(Children[source][i]);
  }
  dfsNum[source] = counter;
}


int lowbit(int x){return x & -x;}
int getSum(int x){
  int sum = 0;
  while(x > 0){
    sum += bit[x];
    x -= x & -x;
  }
  return sum;
}
void setVal(int x, int v){
  if(x == 0) return;
  while(x <= N){
    bit[x] += v;
    x += x & -x;
  }
}
int main(){
  while(~scanf("%d", &N)){
    memset(bit, 0, (N + 1) * sizeof(int));
    memset(dfsNum, 0, (N + 1) * sizeof(int));
    memset(newphe, 0, (N + 1) * sizeof(int));
    for(int i = 1; i <= N; ++i){
      setVal(i, 1);
    }

    int u, v;
    for(int i = 1; i < N; ++i){
      scanf("%d%d", &u, &v);
      Children[u].push_back(v);
    }

    dfs(1);

    scanf("%d", &M);
    vector<bool> apple(N + 1, 1);
    char c[2];
    int x;
    for(int i = 1; i <= M; ++i){
      scanf("%s%d", &c, &x);
      if(c[0] == 'Q'){
        printf("%d\n", getSum(dfsNum[x]) - getSum(newphe[x] - 1));
      }
      if(c[0] == 'C'){
        if(apple[x] == 0){
          setVal(newphe[x], 1);
        }
        else{
          setVal(newphe[x], -1);
        }
        apple[x] = !apple[x];
      }
    }
  }
  return 0;
}