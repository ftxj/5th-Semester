#include <iostream>
#include <cstring>
#include <set>
#include <stack>
#include <vector>
#define MAXN 50010
#define MAXM 50010
using namespace std;
int N, M;
int flag[MAXN];
int main(){
  std::ios::sync_with_stdio(false);
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  cin >> N >> M;
  memset(flag, 0, sizeof(int) * MAXN);
  stack<int> destoryStack;
  set<int> destorySet;
  char Order;
  int index;
  set<int>::iterator before;
  set<int>::iterator after;
  for(int i = 0; i < M; ++i){
    cin >> Order;
    switch(Order){
      case 'D' : 
        cin >> index; 
        if(flag[index] == 0){
          destoryStack.push(index); 
          destorySet.insert(index); 
        }
        flag[index] = 1;
        break;
      case 'Q' : 
        cin >> index;
        before = destorySet.lower_bound(index);
        after = destorySet.upper_bound(index);
        if(destorySet.empty()) 
          cout << N << endl;
        else if(after == destorySet.end()) {
          if(before != destorySet.end()) cout << 0 << endl;
          else cout << N - *(--destorySet.end()) << endl;
        }
        else{
          if(*before == index) cout << 0 << endl;
          else if(before != destorySet.begin()) cout << *after - *(--before) - 1 << endl;
          else cout << *destorySet.begin() - 1 << endl;
        }
        break;
      case 'R' : 
        index = destoryStack.top(); 
        flag[index] = 0;
        destoryStack.pop();
        destorySet.erase(index); 
        break;
    }
  }
  return 0;
}