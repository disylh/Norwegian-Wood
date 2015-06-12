/*
ID: disylh2
PROG: ttwo
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

#define N 10

int xd[] = {0, 1, 0, -1}, yd[] = {-1, 0, 1, 0};

int solve(vector<string> &g, int cy, int cx, int fy, int fx) {
  int cd = 0, fd = 0;
  //cout << "cy " << cy << " cx " << cx << " fy " << fy << " fx " << fx << endl;
  for (int i = 0, ncy, ncx, nfy, nfx; i < N * N * 3 * 2; ++i) {
    //cout << i << endl;
    ncy = cy + yd[cd];
    ncx = cx + xd[cd];
    nfy = fy + yd[fd];
    nfx = fx + xd[fd];
    if (ncy < 0 || ncy >= N || ncx < 0 || ncx >= N || g[ncy][ncx] == '*') {
      cd = ++cd % 4;
    } else {
      cy = ncy;
      cx = ncx;
    }
    if (nfy < 0 || nfy >= N || nfx < 0 || nfx >= N || g[nfy][nfx] == '*') {
      fd = ++fd % 4;
    } else {
      fy = nfy;
      fx = nfx;
    }
    if (cx == fx && cy == fy) {
      return i + 1;
    }
  }
  //cout << "cy " << cy << " cx " << cx << " fy " << fy << " fx " << fx << endl;
  return 0;
}

int main() {
  ofstream fout("ttwo.out");
  ifstream fin("ttwo.in");
  vector<string> g(N, string(N, ' '));
  int cx, cy, fx, fy;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      fin >> g[i][j];
      if (g[i][j] == 'C') {
        cy = i;
        cx = j;
      } else if (g[i][j] == 'F') {
        fy = i;
        fx = j;
      }
    }
    fin.get();
  }
  fin.close();
  fout << solve(g, cy, cx, fy, fx) << endl;
  fout.close();
  return 0;
}
