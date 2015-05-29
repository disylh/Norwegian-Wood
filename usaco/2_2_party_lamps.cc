/*
ID: disylh2
PROG: lamps
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

string to_binary(int c, int w) {
  string ret;
  for (int i = 0; i < w; ++i) {
    if ((c >> i) % 2) {
      ret += '1';
    } else {
      ret += '0';
    }
  }
  return string(ret.begin(), ret.end());
}

vector<vector<int> > gen_p() {
  vector<int> op = {0xfff, 0x555, 0xaaa, 0x249};
  vector<bool> used(1 << 12, false);
  vector<vector<int>> ret;
  ret.push_back({0xfff});
  int last = 0;
  while (true) {
    fill_n(used.begin(), used.size(), false);
    for (auto &v : ret[last]) {
      for (auto &o : op) {
        used[v ^ o] = true;
      }
    }
    ret.push_back(vector<int>());
    for (int i = 0, n = used.size(); i < n; ++i) {
      if (used[i]) {
        ret.back().push_back(i);
      }
    }
    if (ret.back().size() == ret[last].size()) {
      bool cov = true;
      for (int i = 0, n = ret.back().size(); i < n && cov; ++i) {
        cov = ret.back()[i] == ret[last][i];
      }
      if (cov) {
        return ret;
      }
    }
    ++last;
  }
}

void solve(int n, int c, vector<bool> &on, vector<bool> &off, ofstream &fout) {
  vector<string> res;
  int pon = 0, poff = 0;
  bool possible = false;
  auto p = gen_p();
  for (int i = 0; i < n; i += 12) {
    for (int j = i; j < min(i + 12, n); ++j) {
      if (on[j]) {
        pon |= 1 << (j - i);
      }
      if (off[j]) {
        poff |= 1 << (j - i);
      }
    }
    if (pon & poff) fout << "IMPOSSIBLE" << endl;
  }
  c = c >= p.size() ? (p.size() - 1) : c;
  for (auto &v : p[c]) {
    if ((int)(pon & v) == (int)pon && (int)((~v) & poff) == (int)(poff)) {
      string str;
      for (int i = 0; i < n; i += 12) {
        str += to_binary(v, min(n - i, 12));
      }
      possible = true;
      res.push_back(str);
    }
  }
  if (!possible) {
    fout << "IMPOSSIBLE" << endl;
  } else {
    sort(res.begin(), res.end());
    for (auto &s : res) {
      fout << s << endl;
    }
  }
}

int main() {
  ofstream fout("lamps.out");
  ifstream fin("lamps.in");
  int n, c, x;
  fin >> n >> c;
  vector<bool> on(n, false), off(n, false);
  while (true) {
    fin >> x;
    if (x == -1) break;
    on[x - 1] = true;
  }
  while (true) {
    fin >> x;
    if (x == -1) break;
    off[x - 1] = true;
  }
  fin.close();
  solve(n, c, on, off, fout);
  fout.close();
  return 0;
}
