/*
ID: disylh2
PROG: milk2
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

pair<int,int> solve(vector<pair<int,int> > &data) {
  sort(data.begin(), data.end());
  int n = data.size(), lm = 0, lnm = 0;
  for (int i = 0, s = -1, e = -1; i < n; ++i) {
    if (data[i].first > e) {
      if (e != -1) {
        lnm = max(lnm, data[i].first - e);
      }
      s = data[i].first;
      e = data[i].second;
    } else if (data[i].second > e) {
      e = data[i].second;
    }
    lm = max(lm, e - s);
  }
  return {lm, lnm};
}

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    int n, s, e;
    fin >> n;
    vector<pair<int, int> > data;
    for (int i = 0; i < n; ++i) {
      fin >> s >> e;
      data.push_back({s, e});
    }
    auto res = solve(data);
    fout << res.first << " " << res.second << endl;
    return 0;
}
