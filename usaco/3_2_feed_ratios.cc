/*
ID: disylh2
PROG: ratios
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

int check(vector<int> &t, vector<int> &g) {
  int r = 0, curr = 0;
  for (int i = 0; i < 3; ++i) {
    if ((g[i] * t[i] == 0) && g[i] != t[i]) return -1;
    if (g[i] == 0) continue;
    if (t[i] % g[i] != 0) return -1;
    curr = t[i] / g[i];
    if (curr == 0) {
      return -1;
    } else if (r == 0) {
      r = curr;
    } else if (r != curr) {
      return -1;
    }
  }
  return r;
}

void solve(vector<vector<int> > &grains, vector<int> &goal, ofstream &fout) {
  vector<int> ret(3, 0), tmp(3, 0);
  int curr = -1, r;
  for (int i = 0, cr = 0; i < 100; ++i) {
    if (curr != -1 && i >= curr) break;
    for (int j = 0; j < 100; ++j) {
      if (curr != -1 && i + j >= curr) break;
      for (int k = 0; k < 100; ++k) {
        if (curr != -1 && i + j + k >= curr) break;
        tmp[0] = grains[0][0] * i + grains[1][0] * j + grains[2][0] * k;
        tmp[1] = grains[0][1] * i + grains[1][1] * j + grains[2][1] * k;
        tmp[2] = grains[0][2] * i + grains[1][2] * j + grains[2][2] * k;
        if ((cr = check(tmp, goal)) != -1 && (curr == -1 || i + j + k < curr)) {
          curr = i + j + k;
          r = cr;
          ret = {i, j, k};
        }
      }
    }
  }
  if (curr == -1) {
    fout << "NONE" << endl;
  } else {
    fout << ret << r << endl;
  }
}

int main() {
  ofstream fout("ratios.out");
  ifstream fin("ratios.in");
  vector<vector<int> > grains(3, vector<int>(3, 0));
  vector<int> goal(3, 0);
  for (int i = 0; i < 3; ++i) {
    fin >> goal[i];
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      fin >> grains[i][j];
    }
  }
  fin.close();
  solve(grains, goal, fout);
  fout.close();
  return 0;
}

