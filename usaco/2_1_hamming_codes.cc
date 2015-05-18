/*
ID: disylh2
PROG: hamming
LANG: C++11
*/
#include <climits>
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

int hamming_dist(int a, int b) {
  a ^= b;
  int ret = 0;
  while (a) {
    ++ret;
    a &= a - 1;
  }
  return ret;
}

bool dfs(int n, int d, vector<bool> &m, int curr) {
  int bm = m.size();
  bool good = true;
  for (int i = 0; i < curr; ++i) {
    if (m[i] && hamming_dist(i, curr) < d) {
      good = false;
    }
  }
  if (!good) return false;
  m[curr] = true;
  --n;
  if (n == 0) return true;
  for (int i = curr + 1; i < bm; ++i) {
    if (dfs(n, d, m, i)) {
      return true;
    }
  }
  return false;
}


void solve(int n, int b, int d, ofstream &fout) {
  int bm = (1 << (b + 1)) - 1;
  vector<bool> m(bm + 1, false);
  dfs(n, d, m, 0);
  for (int i = 0, c = 0; i <= bm; ++i) {
    if (!m[i]) continue;
    if (c % 10 == 0) fout << i;
    else if (c % 10 == 9 || c == n - 1) fout << " " << i << endl;
    else fout << " " << i;
    ++c;
  }
}

int main() {
    ofstream fout ("hamming.out");
    ifstream fin ("hamming.in");
    int n, b, d;
    fin >> n >> b >> d;
    fin.close();
    solve(n, b, d, fout);
    fout.close();
    return 0;
}
