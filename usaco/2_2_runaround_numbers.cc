/*
ID: disylh2
PROG: runround
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

bool check_num(int n) {
  string s = to_string(n);
  int w = s.size(), i = 0;
  vector<bool> has(10, false), used(w, false);
  for (int curr = s[0] - '0'; !used[i]; i = (curr + i) % w, curr = s[i] - '0') {
    if (has[curr] || curr == 0) return false;
    used[i] = true;
    has[curr] = true;
  }
  if (i != 0) return false;
  for (i = 0; i < w; ++i) {
    if (!used[i]) {
      return false;
    }
  }
  return true;
}

int solve(int n) {
  ++n;
  while (n < 1000000000 && !check_num(n)) {
    ++n;
  }
  return n;
}

int main() {
  ofstream fout("runround.out");
  ifstream fin("runround.in");
  int n;
  fin >> n;
  fin.close();
  fout << solve(n) << endl;
  fout.close();
  return 0;
}
