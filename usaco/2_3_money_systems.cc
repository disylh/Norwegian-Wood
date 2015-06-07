/*
ID: disylh2
PROG: money
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

long long solve(vector<int> &values, int n) {
  vector<long long> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 0, sz = values.size(); i < sz; ++i) {
    for (int j = values[i]; j <= n; ++j) {
      dp[j] += dp[j - values[i]];
    }
  }
  return dp[n];
}

int main() {
  ofstream fout("money.out");
  ifstream fin("money.in");
  int sz, n;
  fin >> sz >> n;
  vector<int> values(sz, 0);
  for (int i = 0; i < sz; ++i) {
    fin >> values[i];
  }
  fin.close();
  fout << solve(values, n) << endl;
  fout.close();
  return 0;
}
