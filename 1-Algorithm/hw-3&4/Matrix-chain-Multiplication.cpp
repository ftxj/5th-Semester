#include <iostream>
#include <cstring>
#include <cstddef>
#include <algorithm>
int main(){
  int n, r, c; 
  int chain[401];
  uint64_t dp[401][401];
  while(std::cin >> n){
    memset(dp, 0xff, 401 * 401 * sizeof(uint64_t));
    for(int i = 0; i < n; ++i){
      std::cin >> r >> c;
      chain[i] = r;
    }
    chain[n] = c;

    dp[0][0] = 0;
    for(int i = 0; i < n; ++i){
      dp[i][0] = 0;
      dp[i][1] = 0;
    }
    for(int L = 2; L <= n; ++L){
      for(int i = 0; i <= n - L; ++i){
        for(int j = 1; j < L; ++j){
          dp[i][L] = std::min(dp[i][L], 
            dp[i][j] + dp[i + j][L - j] + (uint64_t)chain[i] * chain[i + j] * chain[i + L]);
         }
      }
    }
    std::cout << dp[0][n] << std::endl;
  }
  return 0;
}