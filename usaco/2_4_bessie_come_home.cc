/*
ID: disylh2
PROG: comehome
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

int getid(char c) { return c >= 'a' ? (26 + c - 'a') : (c - 'A'); }

void solve(vector<int> &g, ofstream &fout) { 
  vector<int> dist(52, INT_MAX); 
  vector<bool> visited(52, false);
  dist[25] = 0;
  int curr = -1;
  for (int i = 0; i < 52; ++i) {
    curr = -1;
    for (int j = 0; j < 52; ++j) {
       if (!visited[j] && (curr == -1 || dist[curr] > dist[j])) {
         curr = j;
       }
    }
    visited[curr] = true;
    for (int j = 0; j < 52; ++j) {
      if (!visited[j] && g[curr * 52 + j] != -1 &&
          dist[j] > dist[curr] + g[curr * 52 + j]) {
        dist[j] = dist[curr] + g[curr * 52 + j];
      } 
    }
  }
  int res = min_element(dist.begin(), dist.begin() + 25) - dist.begin();
  fout << char(res + 'A') << " " << dist[res] << endl;
}

int main() {
  ofstream fout("comehome.out");
  ifstream fin("comehome.in");
  int n, temp;
  char c1, c2;
  fin >> n;
  vector<int> g(52 * 52, -1);
  for (int i = 0; i < n; ++i) {
    fin >> c1 >> c2 >> temp;
    if (g[getid(c1) * 52 + getid(c2)] == -1 ||
        g[getid(c1) * 52 + getid(c2)] > temp) {
      g[getid(c2) * 52 + getid(c1)] = g[getid(c1) * 52 + getid(c2)] = temp;
    }
  }
  for (int i = 0; i < 52; ++i) {
    g[i * 52 + i] = 0;
  }
  fin.close();
  solve(g, fout);
  fout.close();
  return 0;
}
