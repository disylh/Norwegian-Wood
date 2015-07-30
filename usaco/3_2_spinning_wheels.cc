/*
ID: disylh2
PROG: spin
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

bool check(vector<vector<pair<int,int> > > &wedges, int l, int r, int curr) {
  if (l > r) return false;
  if (curr == wedges.size()) return true;
  int cl, cr;
  for (const auto &p : wedges[curr]) {
    cl = p.first;
    cr = cl + p.second;
    if (check(wedges, max(cl, l), min(r, cr), curr + 1)) {
      return true;
    }
    if (r >= 360 || cr >= 360) {
      if (check(wedges, min(cl, l), min(r % 360, cr % 360), curr + 1)) {
        return true;
      }
    }
  }
  return false;
}

bool check(vector<vector<pair<int,int> > > &wedges) {
  if (wedges.size() == 0) return false;
  for (const auto &p : wedges[0]) {
    if (check(wedges, p.first, p.first + p.second, 1)) {
      return true;
    }
  }
  return false;
}

bool check2(vector<vector<pair<int,int> > > &wedges) {
  int n = wedges.size();
  if (n == 0) return false;
  vector<int> wheels(360, 0);
  for (int i = 0; i < n; ++i){
    for (int j = 0, jn = wedges[i].size(); j < jn; ++j) {
      for (int k = wedges[i][j].first,
               kn = wedges[i][j].first + wedges[i][j].second;
           k <= kn; ++k) {
        ++wheels[k % 360];
      }
    }
  }
  for (const auto &val : wheels) {
    if (val == n) {
      return true;
    }
  }
  return false;
}

void solve(vector<int> &speed, vector<vector<pair<int,int> > > &wedges, ofstream &fout) {
  int n = speed.size();
  if (check2(wedges)) {
    fout << 0 << endl;
    return;
  }
  for (int i = 1; i < 360; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0, kn = wedges[j].size(); k < kn; ++k) {
        wedges[j][k].first = (wedges[j][k].first + speed[j]) % 360;
      }
    }
    if (check2(wedges)) {
      fout << i << endl;
      return;
    }
  }
  fout << "none" << endl;
}

int main() {
  ofstream fout("spin.out");
  ifstream fin("spin.in");
  vector<int> speed(5, 0);
  vector<vector<pair<int,int> > > wedges(5, vector<pair<int,int> >());
  for (int i = 0, n = 0; i < 5; ++i) {
    fin >> speed[i];
    fin >> n;
    for (int j = 0; j < n; ++j) {
      wedges[i].push_back(make_pair(0, 0));
      fin >> wedges[i][j].first >> wedges[i][j].second;
    }
  }
  fin.close();
  solve(speed, wedges, fout);
  fout.close();
  return 0;
}
