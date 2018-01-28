#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class interval{
public:
    double s;
    double f;
    int th;
};
struct cmp{
  bool operator()(interval a, interval b){
    return a.f > b.f;
  }
};

int main(){
  int n = 0;
  cin >> n;
  interval val;
  vector<interval> R;
  priority_queue<interval, vector<interval>, cmp> H;
  for(int i = 0; i < n; ++i){
    cin >> val.s >> val.f;
    val.th = i + 1;
    H.push(val);
  }
  for(int i = 0; i < n; ++i){
    interval t = H.top();
    H.pop();
    if(R.empty()){
      R.push_back(t);
    }
    if(t.s >= R[R.size() - 1].f){
      R.push_back(t);
    }
  }
  cout << "task " << R.size() << " :";
  for(auto i : R){
    cout << i.th << " ";
  }
  return 0;
}