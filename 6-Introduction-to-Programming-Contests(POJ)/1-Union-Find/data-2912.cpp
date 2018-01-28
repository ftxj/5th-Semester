#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[]) {
  int N, M;
  srand((unsigned)time(NULL));
  N = std::atoi(argv[1]);
  M = std::atoi(argv[2]);


  cout << N << endl;
  cout << M << endl;

  vector<int> hash(N, 0);
  map<int, int> Map;

  int judge = rand() % N;
  hash[judge] = 1;
  int index;
  for(int i = 0; i < N - 1; ++i){
    int k = rand() % N;
    while(hash[k] == 1){
      k = rand() % N;
    }
    hash[k] = 1;
    index = rand() % 3;
    Map[k] = index;
  }


  for(int i = 0; i < M; ++i){
    int u = rand() % N;
    int v = rand() % N;
    int c = 0;
    if(u == v){
      c = 0;
    }
    else if(u == judge || v == judge){
      c = rand() % 3;
    }
    else if(Map[u] == Map[v]){
      c = 0;
    }
    else if(((Map[u] + 1) % 3 ) == Map[v]){
      c = 1;
    }
    else if(Map[u] == ((Map[v] + 1)%3)){
      c = 2;
    }
    cout << u << (c == 0? '=':(c == 1? '<':'>')) << v << endl;
  }
  cout << judge;
	return 0;
}