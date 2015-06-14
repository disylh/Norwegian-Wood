/*
ID: disylh2
PROG: stamps
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

int solve(vector<int> &stamps, int k) {
  int sn = stamps.size();
  int dpsz = *max_element(stamps.begin(), stamps.end()) * 2;
  vector<int> dp(dpsz, INT_MAX);
  dp[0] = 0;
  int curr = 0, ret = -1;
  while (dp[curr] <= k) {
    for (int i = 0; i < sn; ++i) {
      dp[(curr + stamps[i]) % dpsz] =
          min(dp[curr] + 1, dp[(curr + stamps[i]) % dpsz]);
    }
    dp[curr] = INT_MAX;
    curr = (curr + 1) % dpsz;
    ++ret;
  }
  return ret;
}

int main() {
  ofstream fout("stamps.out");
  ifstream fin("stamps.in");
  int k, n;
  fin >> k >> n;
  vector<int> stamps(n, 0);
  for (int i = 0; i < n; ++i) {
    stamps[i];
    fin >> stamps[i];
  }
  fin.close();
  fout << solve(stamps, k) << endl;
  fout.close();
  return 0;
}
