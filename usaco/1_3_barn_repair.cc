/*
ID: disylh2
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int solve(const vector<bool> &barns, int m) {
  int ret = 0, f = -1, l = -1, n = barns.size();
  vector<int> dist(n, 0);
  for (int i = 0, pre = -1; i < n; ++i) {
    if (!barns[i]) continue;
    if (f == -1) {
      pre = f = i;
    } else {
      ++dist[i-pre-1];
      pre = i;
    }
    l = i;
  }
  ret = l - f + 1;
  for (int i = n - 1, c = m - 1; i >= 0 && c; --i) {
    if (dist[i] > 0) {
      ret -= min(c, dist[i]) * i;
      c -= min(c, dist[i]);
    }
  }
  return ret;
}

int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    int m, s, c, sn;
    fin >> m >> s >> c;
    vector<bool> barns(s + 1, false);
    vector<pair<int, int> > data;
    for (int i = 0; i < c; ++i) {
      fin >> sn;
      barns[sn] = true;
    }
    fout << solve(barns, m) << endl;
    return 0;
}
