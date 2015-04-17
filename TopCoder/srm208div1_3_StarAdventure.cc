#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

using namespace std;

class StarAdventure {
 public:
  int mostStars(vector<string> level) {
    int m = level.size(), n = level[0].size();
    if (m < n) {
      level = transports(level);
    }
    return solve(level);
  }
  vector<string> transports(const vector<string> &level) {
    int m = level.size(), n = level[0].size();
    vector<string> ret(n, "");
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ret[i] += level[j][i];
      }
    }
    return ret;
  }
  int solve(const vector<string> &level) {
    int m = level.size(), n = level[0].size();
    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(n, vector<int>(n, 0)));
    vector<int> sum(n, 0);
    for (int l = 0, iv = 0, jv = 0, kv = 0, mx = 0; l < m; ++l) {
      for (int i = 0; i < n; ++i) {
        iv = level[l][i] - '0';
        sum[i] = (i == 0 ? 0 : sum[i-1]) + iv;
        for (int j = i; j < n; ++j) {
          jv = level[l][j] - '0';
          for (int k = j; k < n; ++k) {
            kv = level[l][k] - '0';
            dp[i][j][k] += iv;
            if (j != i) {
              dp[i][j][k] += jv;
            }
            if (k != j) {
              dp[i][j][k] += kv;
            }
          }
        }
      }
      for (int k = 0; k < n; ++k) {
        for (int j = k; j > 0; --j) {
          mx = dp[0][j][k] - sum[0];
          for (int i = 0; i <= j; ++i) {
            dp[i][j][k] = max(dp[i][j][k], (i == j ? sum[i-1] : sum[i]) + mx);
            mx = max(mx, dp[i][j][k] - sum[i]);
          }
        }
      }
      for (int k = 0; k < n; ++k) {
        for (int i = k - 1; i >= 0; --i) {
          mx = dp[i][i+1][k] - sum[i+1];
          for (int j = i + 1; j <= k; ++j) {
            dp[i][j][k] = max(dp[i][j][k], (j == k ? sum[j-1] : sum[j]) + mx);
            mx = max(mx, dp[i][j][k] - sum[j]);
          }
        }
      }
      for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
          mx = dp[i][j][j+1] - sum[j+1];
          for (int k = j + 1; k < n; ++k) {
            dp[i][j][k] = max(dp[i][j][k], sum[k] + mx);
            mx = max(mx, dp[i][j][k] - sum[k]);
          }
        }
      }
    }
    return dp[n - 1][n - 1][n - 1];
  }
};  

int main() {
  vector<string> s({"0234342522", "1232142445"});
  StarAdventure sa;
  int ret = sa.mostStars(s);
  cout << ret << endl;
  assert(ret == 55);
}

