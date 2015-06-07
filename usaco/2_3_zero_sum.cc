/*
ID: disylh2
PROG: zerosum
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

void solve(vector<char> &bt, int curr, int sum, int last, ofstream &fout) { 
  int n = bt.size();
  if (curr == n) {
    if (sum == 0) {
      fout << "1";
      for (int i = 0; i < n; ++i) {
        fout << bt[i] << i + 2;
      }
      fout << endl;
    }
    return;
  }
  bt[curr] = ' ';
  solve(bt, curr + 1, sum - last + 10 * last + (last > 0 ? 1 : -1) * (curr + 2), last * 10 + curr + 2, fout);
  bt[curr] = '+';
  solve(bt, curr + 1, sum + curr + 2, curr + 2, fout);
  bt[curr] = '-';
  solve(bt, curr + 1, sum - curr - 2, -(curr + 2), fout);
}


int main() {
  ofstream fout("zerosum.out");
  ifstream fin("zerosum.in");
  int n;
  fin >> n;
  fin.close();
  vector<char> bt(n - 1, 0);
  solve(bt, 0, 1, 1, fout);
  fout.close();
  return 0;
}
