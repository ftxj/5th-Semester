#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
#define MAXN 20010
long long  N, maxIndex;
long long  lowbit(long long  x) {return x & -x;}
long long  changeVal(long long * arg, long long  index, long long  value){
  while(index <= maxIndex){
    arg[index] += value;
    index += lowbit(index);
  }
}
long long  getSum(long long  *arg, long long  index){
  long long  sum = 0;
  while(index > 0){
    sum += arg[index];
    index -= lowbit(index);
  }
  return sum;
}

struct Moo{
  long long  volume;
  long long  index;
};

struct cmp{
  bool operator()(const Moo &a, const Moo &b){
    return a.volume < b.volume;    
  }
};


Moo MooFest[MAXN];
long long  countSmaller[MAXN];
long long  sumSmaller[MAXN];

int main(){
  long long  res = 0;
  maxIndex = 0;
  cin >> N; 
  if(N == 0) {cout << "0" << endl; return 0;}
  for(long long  i = 0; i < N; ++i){
    cin >> MooFest[i].volume >> MooFest[i].index;
    maxIndex = max(maxIndex, MooFest[i].index);
  }

  memset(countSmaller, 0, sizeof(long long ) * maxIndex);
  memset(sumSmaller, 0, sizeof(long long ) * maxIndex);

  sort(MooFest, MooFest + N, cmp());

  /*for(long long  i = 0; i < N; ++i){
    cout << MooFest[i].volume << "," << MooFest[i].index << endl;
  }*/

  long long  tempSum = 0, smallerCount, bigerCount, smallerSum;
  changeVal(countSmaller, MooFest[0].index, 1);
  changeVal(sumSmaller, MooFest[0].index, MooFest[0].index);
  tempSum = MooFest[0].index;
  for(long long  i = 1; i < N; ++i){
    tempSum += MooFest[i].index;
    smallerCount = getSum(countSmaller, MooFest[i].index);
    smallerSum = getSum(sumSmaller, MooFest[i].index);    
    //cout << "t:" << smallerCount  << "," << smallerSum << endl;
    bigerCount = i - smallerCount + 1;
    res += (
        (tempSum - 2 * smallerSum) + 
        ((smallerCount  - bigerCount)* MooFest[i].index)
        ) * MooFest[i].volume;

    changeVal(countSmaller, MooFest[i].index, 1);
    changeVal(sumSmaller, MooFest[i].index, MooFest[i].index);
  }
  cout << res << endl;  
  return 0;
}
