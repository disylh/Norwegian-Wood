/*
ID: disylh2
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

int solve(const string &str) {
  string s = str + str;
  char c = 'w';
  int n = s.size(), ret = -1, last = 0, start = 0; 
  for (int i = 0, lw = -1; i < n; ++i) {
    if (s[i] != 'w' && s[i] != c) {
      ret = max(ret, n / 2 < last + i - start ? n / 2 : last + i - start);
      if (ret == n / 2) return ret;
      last = lw - start + 1;
      start = lw + 1;
      c = s[i];
    } 
    if (s[i] != 'w') {
      lw = i;
    }
  }
  ret = max(ret, n / 2 < last + n - start ? n / 2 : last + n - start);
  return ret == -1 ? n / 2 : ret;
}

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
    int n = 0, res = 0;
    string str;
    fin >> n >> str;
    fout << solve(str) << endl;
    return 0;
}
