/*
ID: disylh2
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool check(const vector<pair<int,int> > &data, const vector<int> &p) {
  int n = data.size();
  vector<bool> used(n, false);
  for (int i = 0; i < n - 1; ++i) {
    if (used[i]) continue;;
    int m = i;
    while (m + 1 < n && data[m].first == data[m+1].first && p[m+1] != i) {
      m = p[m+1];
    }
    if (m + 1 == n || data[m].first != data[m+1].first) {
      m = i;
      while (m + 1 < n && data[m].first == data[m+1].first && p[m+1] != i) {
        used[m] = false;
        m = p[m+1];
      } 
      used[m] = false;
      continue;
    }
    return true;
  }
  return false;
}

int all_pairs(vector<pair<int,int> > &data, vector<int> &p, int n, int curr) {
  if (curr == n) {
    return check(data, p) ? 1 : 0;
  } else if (p[curr] != curr) {
    return all_pairs(data, p, n, curr + 1);
  }
  int ret = 0;
  for (int i = curr + 1; i < n; ++i) {
    if (i == p[i]) {
      swap(p[curr], p[i]);
      ret += all_pairs(data, p, n, curr + 1);
      swap(p[curr], p[i]);
    }
  }
  return ret;
}

int solve(vector<pair<int,int> > &data) {
  int n = data.size(); 
  vector<int> p(n, 0);
  sort(data.begin(), data.end());
  for (int i = 0; i < n; ++i) {
    p[i] = i;
  }
  return all_pairs(data, p, n, 0);
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");
    int n, x, y;
    fin >> n;
    vector<pair<int, int> > data;
    for (int i = 0; i < n; ++i) {
      fin >> x >> y;
      data.push_back(make_pair(y, x));
    }
    fout << solve(data) << endl;
    return 0;
}
