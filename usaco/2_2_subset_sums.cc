/*
ID: disylh2
PROG: subset
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>

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

int count(int target, int curr, vector<int> &cache, int n) {
  int cpos = target * n + curr;
  if (cache[cpos] != -1) {
    return cache[cpos];
  }
  target -= curr;
  if (target == 0) {
    return cache[cpos] = 1;
  }
  int ret = 0;
  for (int i = curr - 1; i >= 1; --i) {
    if (target - i >= 0) {
      ret += count(target, i, cache, n);
    }
  }
  return cache[cpos] = ret;
}

int solve(int n) { 
  if (n * (n + 1) / 2 % 2) {
    return 0;
  }
  int target = n * (n + 1) >> 2;
  vector<int> cache((target + 1) * (n + 1), -1);
  int ret = count(target, n, cache, n);
  return ret;
}

int solve2(int n) {
  if (n * (n + 1) / 2 % 2) {
    return 0;
  }
  int target = n * (n + 1) >> 2;
  vector<long long> dp(target + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = target; j >= i; --j) {
      dp[j] += dp[j-i];
    }
  }
  return dp[target] / 2;
}

int main() {
  ofstream fout("subset.out");
  ifstream fin("subset.in");
  int n;
  fin >> n;
  fin.close();
  fout << solve2(n) << endl;
  fout.close();
  return 0;
}
