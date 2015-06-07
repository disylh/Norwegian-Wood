/*
ID: disylh2
PROG: nocows
LANG: C++11
*/
#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T, typename TT>
ostream &operator<<(ostream &s, pair<T, TT> t) {
  return s << "(" << t.first << "," << t.second << ")";
}
template <typename T>
ostream &operator<<(ostream &s, vector<T> t) {
  for (int i = 0; i < t.size(); ++i) s << t[i] << " ";
  return s;
}

#define MOD 9901

int solve(unsigned int n, unsigned int k) {
  vector<vector<int> > dp(k + 1, vector<int>(n + 1, 0)),
      dps(k + 1, vector<int>(n + 1, 0));
  dp[1][1] = dps[1][1] = 1;
  for (unsigned int i = 2; i <= k; ++i) {
    for (unsigned int j = 1; j <= n; j += 2) {
      for (unsigned int s = 1; s <= j - 1; s += 2) {
        dp[i][j] = (dp[i][j] +
                    (dps[i - 1][s] * dps[i - 1][j - s - 1] % MOD -
                     dps[i - 2][s] * dps[i - 2][j - s - 1] % MOD + MOD) %
                        MOD) %
                   MOD;
      }
      dps[i][j] = (dps[i - 1][j] + dp[i][j]) % MOD;
    }
  }
  return dp[k][n];
}

int main() {
  ofstream fout("nocows.out");
  ifstream fin("nocows.in");
  int n, k;
  fin >> n >> k;
  fin.close();
  fout << solve(n, k) << endl;
  fout.close();
  return 0;
}
