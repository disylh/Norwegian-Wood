/*
ID: disylh2
PROG: holstein
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

void dfs(int v, int g, vector<int> &vtm, vector<vector<int> > &feeds, vector<bool> &fc, int n, int &nmin, int curr, vector<bool> &res) {
  if (n + 1 >= nmin || curr == g) {
    return;
  }
  for (int i = curr; i < g && n + 1 < nmin; ++i) {
    fc[i] = true;
    bool meet = true;
    for (int j = 0; j < v; ++j) {
      vtm[j] -= feeds[i][j];
      if (vtm[j] > 0) {
        meet = false;
      }
    }
    if (meet) {
      res = fc;
      nmin = n + 1;
    } else {
      dfs(v, g, vtm, feeds, fc, n + 1, nmin, i + 1, res);
    }
    for (int j = 0; j < v; ++j) {
      vtm[j] += feeds[i][j];
    }
    fc[i] = false;
  }
}

void solve(int v, int g, vector<int> &vtm, vector<vector<int> > &feeds, ofstream &fout) {
  vector<bool> fc(g, false), res;
  int ret = INT_MAX;
  dfs(v, g, vtm, feeds, fc, 0, ret, 0, res);
  fout << ret;
  for (int i = 0; i < g; ++i) {
    if (res[i]) {
      fout << " " << i + 1;
    }
  }
  fout << endl;
}

int main() {
    ofstream fout ("holstein.out");
    ifstream fin ("holstein.in");
    int v, g;
    fin >> v;
    vector<int> vtm(v, 0);
    for (int i = 0; i < v; ++i) {
      fin >> vtm[i];
    }
    fin >> g;
    vector<vector<int> > feeds(g, vector<int>(v, 0));
    for (int i = 0; i < g; ++i) {
      for (int j = 0; j < v; ++j) {
        fin >> feeds[i][j];
      }
    }
    fin.close();
    solve(v, g, vtm, feeds, fout);
    fout.close();
    return 0;
}
