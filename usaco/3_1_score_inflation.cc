/*
ID: disylh2
PROG: inflate
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

int solve(vector<pair<int,int> > &p, int m) {
  int n = p.size();
  vector<int> dp(m + 1, 0);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i + p[j].second <= m) {
        dp[i + p[j].second] = max(dp[i] + p[j].first, dp[i + p[j].second]);
      }
    }
  }
  return dp[m];
}

int main() {
  ofstream fout("inflate.out");
  ifstream fin("inflate.in");
  int m, n;
  fin >> m >> n;
  vector<pair<int, int> > p(n, pair<int, int>(0, 0));
  for (int i = 0; i < n; ++i) {
    fin >> p[i].first >> p[i].second;
  }
  fin.close();
  fout << solve(p, m) << endl;
  fout.close();
  return 0;
}
