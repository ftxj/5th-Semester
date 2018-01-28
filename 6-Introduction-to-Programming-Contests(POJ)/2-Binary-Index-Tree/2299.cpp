#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<iostream>
#include<cwctype>
#define MAXN 500050
using namespace std;

struct node{
  long long val;
  int index;
  bool operator < (const node &v) const {
    return val < v.val;
  }
};

node initData[MAXN];
int smlData[MAXN];
int BIT[MAXN];
int N;

int lowbit(int x) {return x & -x;}
void init(){memset(BIT, 0, (N + 1)*sizeof(int));}
int getsum(int x){
  int sum = 0;
  while(x > 0){
    sum += BIT[x];
    x -= lowbit(x);
  }
  return sum;
}
int addElm(int x, int p){
  while(x <= N){
    BIT[x] += p;
    x += lowbit(x); 
  }
}

int main(){
  while(scanf("%d", &N) && N != 0){
    for(int i = 1; i <= N; ++i){
      scanf("%lld", &initData[i].val);
      initData[i].index = i;
    }
    std::sort(initData + 1, initData + N + 1);
    for(int i = 1; i <= N; ++i) smlData[initData[i].index] = i;
    init();
    long long sum = 0;    
    for(int i = 1; i <= N; ++i){
      addElm(smlData[i], 1);
      sum += i - getsum(smlData[i]);
    }
    printf("%lld\n", sum);
  }
  return 0;
}