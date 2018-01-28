#include <iostream>
#include <cstring>
#include <cstddef>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
  uint32_t m, n1, n2;
  uint32_t sigema[65];
  uint32_t alpha[65][65];
  uint32_t s1[10001], s2[10001];

  while(std::cin >> m){

    for(uint32_t i = 0; i < m; ++i){
      std::cin >> sigema[i];
    }
    
    for(uint32_t i = 0; i < m; ++i){
      for(uint32_t j = 0; j < m; ++j){
        std::cin >> alpha[i][j];
      }
    }

    std::cin >> n1;
    for(uint32_t i = 1; i <= n1; ++i){
      std::cin >> s1[i];
    }

    std::cin >> n2;
    for(uint32_t i = 1; i <= n2; ++i){
      std::cin >> s2[i];
    }
    vector<vector<uint32_t>> dp(max(n1,n2) + 1, vector<uint32_t>(max(n1,n2) + 1, 0));

    dp[0][0] = 0;
    for(uint32_t i = 1; i <= n1; ++i){
      dp[i][0] = dp[i - 1][0] + sigema[s1[i]];
    }
    for(uint32_t i = 1; i <= n2; ++i){
      dp[0][i] = dp[0][i - 1] + sigema[s2[i]];
    }

    for(uint32_t i = 1; i <= n1; ++i){
      for(uint32_t j = 1; j <= n2; ++j){
        dp[i][j] = std::min(dp[i - 1][j - 1] + alpha[s1[i]][s2[j]], 
          std::min(dp[i - 1][j] + sigema[s1[i]], dp[i][j - 1] + sigema[s2[j]]));
      }
    }

    std::cout << dp[n1][n2] << std::endl;
  }
  return 0;
}