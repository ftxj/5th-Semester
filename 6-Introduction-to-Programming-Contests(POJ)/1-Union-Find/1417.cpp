#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cstdio>
#include <algorithm>
#define MAXQ 1000
#define MAXN 500
using namespace std;
int fa[MAXN];
int co[MAXN];
int su[MAXN];
int di[MAXN];
int ha[MAXN];
int Q, divine, devilish;
int find(int u){
  if(u == fa[u]){
    return u;
  }
  else{
    int ans = fa[u];
    fa[u] = find(fa[u]);
    co[u] = co[u] ^ co[ans];
    return fa[u];
  }
}

void merge(int u, int v, int c){
  int pu = find(u);
  int pv = find(v);
  if(pu != pv){
    ha[pu] = 0;
    ha[pv] = 1;
    fa[pu] = pv;
    co[pu] = co[u] ^  co[v] ^ c;
    su[pv] = su[pv] + su[pu];
    di[pv] = co[pu] == 0? di[pv] + di[pu] : (di[pv] + su[pu] - di[pu]);
  }
}

void init(){
  for(int i = 0; i < divine + devilish + 1; ++i){
    fa[i] = i;
    co[i] = 0;
    su[i] = 1;
    di[i] = 1;
    ha[i] = 1;
  }
}

int knapsack(vector<vector<pair<int, int> > >&v, int height, int width, vector<int > &path){
  int minheight = MAXN, minwidth = MAXN;
  for(int i = 0; i < MAXN; ++i){
    if(ha[i] == 1){
      minheight = min(di[i], minheight);
      minwidth = min(su[i] - di[i], minwidth);
    }
  }
	vector<vector<int> > dp(v.size() + 1, vector<int>(height + 1, 0));
	for(int k = 1; k <= v.size(); ++k){
		for(int h = minheight; h <= height; ++h){
				if(h >= v[k-1][0].first){
					dp[k][h] = max(dp[k - 1][h],
						dp[k - 1][h - v[k-1][0].first] + 1);
				}
				if(h >= v[k-1][1].first){
					dp[k][h] = max(max(dp[k][h], dp[k - 1][h]),
						dp[k - 1][h - v[k-1][1].first] + 1);
				}
        dp[k][h] = max(dp[k][h], dp[k-1][h]);
		}
  }
  cout << "debug dp" << endl;
  for(int k = 1; k <= v.size(); ++k){
		for(int h = 1; h <= height; ++h){
				cout << dp[k][h] << endl;
		}
  }
  int sureheight = height, surewidth = width;
  for(int i = v.size(); i > 0; --i){
    if(sureheight - v[i-1][0].first < 0){
      sureheight = sureheight - v[i-1][1].first;
      path.push_back(1);
      continue;
    }
    if(sureheight - v[i-1][1].first < 0){
      sureheight = sureheight - v[i-1][0].first;
      path.push_back(0);
      continue;
    }
    if(dp[i - 1][sureheight - v[i-1][0].first] == 
        dp[i - 1][sureheight - v[i-1][1].first]){
      return 0;
    }
    if(dp[i - 1][sureheight - v[i-1][0].first] == i - 1){
      sureheight = sureheight - v[i-1][0].first;
      path.push_back(0);
    }
    else if(dp[i - 1][sureheight - v[i-1][1].first] == i - 1){
      sureheight = sureheight - v[i-1][1].first;
      path.push_back(1);
    }
    else{
      return 0;
    }
  }
	return dp[v.size()][height] == v.size();
}


int main(){
  int x, y, c;
  char ans[5];
  while(scanf("%d %d %d", &Q, &divine, &devilish) && (Q != 0 || divine != 0 || devilish != 0)){
    init();
    for(int i = 0; i < Q; ++i){
      scanf("%d %d %s", &x, &y, ans);
      if(ans[0] == 'n') c = 1;
      else c = 0;
      merge(x, y, c);
    }
    if(divine == devilish){
      printf("no\n");
      continue;
    }
    if(divine == 0){
      printf("end\n");
      continue;
    }
    else if(devilish == 0){
      for(int i = 1; i <= divine; ++i){
        printf("%d\n", i);
      }
      printf("end\n");
      continue;
    }

    vector<vector<pair<int, int> > >v;
    map<int, int> m;
    for(int i = 1; i <= divine + devilish; ++i){ 
      if(ha[i] == 1){
        vector<pair<int, int> > t;
        t.push_back(make_pair(di[i], su[i] - di[i]));
        t.push_back(make_pair(su[i] - di[i], di[i]));
        v.push_back(t);
        m[i] = v.size() - 1;
      }
    }
    for(int i = 0; i < v.size(); ++i){
      cout << i << "  " << v[i][0].first << "," << v[i][0].second << endl;
      cout << i << "  " << v[i][1].first << "," << v[i][1].second << endl;
    }
    vector<int> path;
    if(!knapsack(v, divine, devilish, path)){
      printf("no\n");
    }
    else{
      // for(int i = 0; i < path.size(); ++i){
      //   cout << path[i] << endl;
      // }
      //cout << "yes" << endl;
      for(int i = 1; i <= devilish + divine; ++i){
        int f = find(i);
        if(path[path.size() - 1 - m[f]]){
          if(co[i] == 1)
            printf("%d\n", i);
        }
        else{
          if(co[i] == 0)
            printf("%d\n", i);
        }
      }
      printf("end\n");
    }
  }
  return 0;
}