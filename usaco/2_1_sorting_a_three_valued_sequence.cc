/*
ID: disylh2
PROG: sort3
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

void sort_3ways(vector<int> &data) {
  int one = 0, two = 0;
  for (int i = 0, n = data.size(); i < n; ++i) {
    if (data[i] == 1) {
      data[i] = 3;
      data[two++] = 2;
      data[one++] = 1;
    } else if (data[i] == 2) {
      data[i] = 3;
      data[two++] = 2;
    }
  }
}

void solve(vector<int> &data, ofstream &fout) {
  int n = data.size(), matched = 0, unmatched = 0;
  vector<int> sorted(data.begin(), data.end());
  sort_3ways(sorted);
  vector<vector<int> > g(4, vector<int>(4, 0));
  for (int i = 0; i < n; ++i) {
    if (data[i] != sorted[i]) {
      ++g[data[i]][sorted[i]];
    }
  }
  for (int i = 1; i <= 3; ++i) {
    for (int j = i + 1; j <= 3; ++j) {
      matched += min(g[i][j], g[j][i]);
      unmatched += max(g[i][j], g[j][i]) - min(g[i][j], g[j][i]);
    }
  }
  fout << matched + unmatched / 3 * 2 << endl;
}

int main() {
    ofstream fout ("sort3.out");
    ifstream fin ("sort3.in");
    int n;
    fin >> n;
    vector<int> data(n, 0);
    for (int i = 0; i < n; ++i) {
      fin >> data[i];
    }
    fin.close();
    solve(data, fout);
    fout.close();
    return 0;
}
