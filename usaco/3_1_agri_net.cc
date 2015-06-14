/*
ID: disylh2
PROG: agrinet
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

int solve(vector<int> &g, int n) {
  vector<int> dist(n, INT_MAX);
  vector<bool> intree(n, false);
  intree[0] = true;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    dist[i] = g[i];
  }
  for (int i = 1, curr = -1; i < n; ++i) {
    curr = -1;
    for (int j = 0; j < n; ++j) {
      if (!intree[j] && (curr == -1 || dist[curr] > dist[j])) {
        curr = j;
      }
    }
    intree[curr] = true;
    ret += dist[curr];
    for (int j = 0; j < n; ++j) {
      if (!intree[j] && g[curr * n + j] < dist[j]) {
        dist[j] = g[curr * n + j];
      }
    }
  }
  return ret;
}

int main() {
  ofstream fout("agrinet.out");
  ifstream fin("agrinet.in");
  int n;
  fin >> n;
  vector<int> g(n * n, 0);
  for (int i = 0, e = n * n; i < e; ++i) {
    fin >> g[i];
  }
  fin.close();
  fout << solve(g, n) << endl;
  fout.close();
  return 0;
}
