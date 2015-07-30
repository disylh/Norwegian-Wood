/*
ID: disylh2
PROG: kimbits
LANG: C++11
*/
#include <cstring>
#include <climits>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iterator>

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

vector<vector<int> > pascal_triangle(int n) {
  vector<vector<int> > ret(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i <= n; ++i) {
    ret[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
    }
  }
  return ret;
}

string solve(int n, int l, long long i) {
  string ret(n, '0');
  vector<vector<int> > pascal = pascal_triangle(n - 1);
  long long curr = 0;
  for (int s = n, t = l; i > 0 && s > 0; --s) {
    curr = 0;
    for (int k = 0, kn = min(t, s - 1); k <= kn; ++k) {
      curr += pascal[s - 1][k];
    }
    if (i > curr) {
      ret[n - s] = '1';
      i -= curr;
      --t;
    }
  }
  return ret;
}

int main() {
  ofstream fout("kimbits.out");
  ifstream fin("kimbits.in");
  int n, l;
  long long i;
  fin >> n >> l >> i;
  fin.close();
  fout << solve(n, l, i) << endl;
  fout.close();
  return 0;
}
