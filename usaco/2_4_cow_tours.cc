/*
ID: disylh2
PROG: cowtour
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
#include <iomanip>
#include <cmath>
#include <limits>

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

double dist(const pair<int, int> &p1, const pair<int, int> &p2) {
  return sqrt((p1.first - p2.first) * (p1.first - p2.first) +
              (p1.second - p2.second) * (p1.second - p2.second));
}

bool is_almost_equal(double a, double b) {
  return fabs(a - b) < numeric_limits<double>::epsilon();
}

double solve(vector<bool> &g, vector<pair<int, int> > &p, int n) {
  vector<double> d(n * n, -1);
  for (int i = 0, e = n * n; i < e; ++i) {
    if (g[i]) {
      d[i] = dist(p[i / n], p[i % n]);
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i != j && !is_almost_equal(d[i * n + k], -1) &&
            !is_almost_equal(d[k * n + j], -1) &&
            (is_almost_equal(d[i * n + j], -1) ||
             d[i * n + j] > d[i * n + k] + d[k * n + j])) {
          d[i * n + j] = d[i * n + k] + d[k * n + j];
        }
      }
    }
  }
  vector<double> dm(n, 0);
  vector<int> lv(n, -1);
  vector<double> dl;
  int ln = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      //cout << d[i * n + j] << " ";
      if (i == j || !is_almost_equal(d[i * n + j], -1)) {
        dm[i] = max(d[i * n + j], dm[i]);
        if (lv[i] == -1 && lv[j] == -1) {
          lv[i] = lv[j] = ln++;
          dl.push_back(dm[i]);
        } else {
          lv[i] = lv[j] = max(lv[i], lv[j]);
          dl[lv[i]] = max(dl[lv[i]], dm[i]);
        }
      }
    }
    //cout << endl;
  }
  double ret = -1, temp = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && is_almost_equal(d[i * n + j], -1)) {
        temp = dm[i] + dm[j] + dist(p[i], p[j]);
        temp = max(max(dl[lv[i]], dl[lv[j]]), temp);
        //cout << "i " << i << " j " << j << " " << temp << " " << dist(p[i],p[j]) << endl;
        if (ret == -1 || ret > temp) {
          //cout << "update" << endl;
          ret = temp;
        }
      }
    }
  }
  //cout << "dm " << dm << endl;
  //cout << lv << endl;
  //cout << dl << endl;
  //cout << ret << endl;
  return ret;
}

int main() {
  ofstream fout("cowtour.out");
  ifstream fin("cowtour.in");
  int n = 0;
  fin >> n;
  vector<pair<int, int> > p(n, pair<int, int>(0, 0));
  vector<bool> g(n * n, false);
  for (int i = 0; i < n; ++i) {
    fin >> p[i].first >> p[i].second;
  }
  fin.get();
  char c;
  for (int i = 0, e = n * n; i < e; ++i) {
    c = fin.get();
    g[i] = c == '1' ? true : false;
    if (i % n == n - 1) {
      fin.get();
    }
  }
  fin.close();
  fout << fixed << setprecision(6) << solve(g, p, n) << endl;
  //fout << solve(g, p, n) << endl;
  fout.close();
  return 0;
}
