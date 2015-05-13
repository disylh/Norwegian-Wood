/*
ID: disylh2
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <initializer_list>

using namespace std;

int mod(int a, int b) { return (a % b + b) % b; }

int overlap(int al, int ah, int bl, int bh, int n) {
  if (al < 0) return overlap(0, ah, bl, bh, n) + overlap(n + al, n - 1, bl, bh, n);
  else if (ah >= n) return overlap(al, n - 1, bl, bh, n) + overlap(0, ah - n, bl, bh, n);
  else if (bl < 0) return overlap(al, ah, 0, bh, n) + overlap(al, ah, n + bl, n - 1, n);
  else if (bh >= n) return overlap(al, ah, bl, n - 1, n) + overlap(al, ah, 0, bh - n, n);
  int ret =  min(ah, bh) - max(al, bl) + 1;
  return ret < 0 ? 0 : ret;
}

int solve(const vector<int> &fl, const vector<int> &ml, int n) {
  if (n <= 5) return n * n * n;
  int dup = 1;
  for (int i = 0, e = 3; i < e; ++i) {
    if (!dup) continue;
    dup *= overlap(fl[i] - 2, fl[i] + 2, ml[i] - 2, ml[i] + 2, n);
  }
  return 5 * 5 * 5 * 2 - dup;
}

int main() {
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");
    int n, a, b, c;
    fin >> n;
    fin >> a >> b >> c;
    vector<int> fl({a, b, c});
    fin >> a >> b >> c;
    vector<int> ml({a, b, c});
    fout << solve(fl, ml, n) << endl;
    return 0;
}
