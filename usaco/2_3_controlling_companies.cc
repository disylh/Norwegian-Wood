/*
ID: disylh2
PROG: concom
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

void solve(vector<vector<pair<int, int> > > &g, ofstream &fout) {
  int n = g.size();
  vector<bool> visited(n, false);
  vector<int> ctrl(n, 0);
  queue<int> q;
  for (int i = 1, curr = 0; i < n; ++i) {
    fill_n(visited.begin(), n, false);
    fill_n(ctrl.begin(), n, 0);
    q.push(i);
    visited[i] = true;
    while(!q.empty()) {
      curr = q.front();
      q.pop();
      for (auto &j : g[curr]) {
        ctrl[j.first] += j.second;
        if (!visited[j.first] && ctrl[j.first] > 50) {
          visited[j.first] = true;
          q.push(j.first);
        }
      }
    }
    for (int j = 1; j < n; ++j) {
      if (i != j && ctrl[j] > 50) {
        fout << i << " " << j << endl;
      }
    }
  }
}


int main() {
  ofstream fout("concom.out");
  ifstream fin("concom.in");
  int n, i, j, p;
  fin >> n;
  vector<vector<pair<int, int> > > g(100 + 1, vector<pair<int, int> >());
  for (int t = 0; t < n; ++t) {
    fin >> i >> j >> p;
    g[i].push_back(pair<int, int>(j, p));
  }
  fin.close();
  solve(g, fout);
  fout.close();
  return 0;
}
