/*
ID: disylh2
PROG: milk
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int solve(vector<pair<int,int> > &data, int req) {
  sort(data.begin(), data.end());
  int n = data.size(), ret = 0;
  for (int i = 0, temp = 0; i < n && req > 0; ++i) {
    temp = min(req, data[i].second);
    ret += data[i].first * temp;
    req -= temp;
  } 
  return ret;
}

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    int n, m, p, a;
    fin >> n >> m;
    vector<pair<int, int> > data;
    for (int i = 0; i < m; ++i) {
      fin >> p >> a;
      data.push_back({p, a});
    }
    fout << solve(data, n) << endl;
    return 0;
}
