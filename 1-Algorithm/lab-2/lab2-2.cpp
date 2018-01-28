#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

void swap(vector<int> &data, int i, int j){
  int temp = data[i];
  data[i] = data[j];
  data[j] = temp;
}

int findKthMin(vector<int> &data, int low, int high, int k){
  if(low == high) return data[low];
  int pivot = data[low];
  int size = high - low  + 1;
  int Lbase = low - 1, Lsize = 0, Rbase = high + 1, Rsize = 0, EquMid = 0, Ebase = Rbase;

  for(int i = low; Lsize + Rsize + EquMid != size;){
    if(data[i] < pivot){
      i++;
      Lbase++;
      Lsize++;
    }
    else{
      swap(data, i, --Rbase);
      if(data[Rbase] == pivot){
        swap(data, Rbase, --Ebase);
        EquMid++;
      }
      else{
        Rsize++;
      }
    }
  }

  if(Lsize >= k){
    return findKthMin(data, low, Lbase, k);
  }
  else if(Lsize + EquMid >= k){
    return pivot;
  }
  else{
    return findKthMin(data, Rbase, high - EquMid, k - Lsize - EquMid);
  }
}

int main(){
  int total, k;
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  while(scanf("%d %d", &total, &k) == 2){
    if(total == 0) break;
    vector<int> data(total);
    for(int i = 0; i < total; ++i){
      scanf("%d", &data[i]);
    }
    printf("%d\n", findKthMin(data, 0, data.size() - 1, k));
  }
  return 0;
}