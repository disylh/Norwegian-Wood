/*
ID: disylh2
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int solve(vector<int> &data) {
  int n = data.size(), l = 0, h = n - 1, ls = 0, hs = 0, lm = 0, hm = 0, lc, hc,
      lret = 0, hret = 0;
  while (h - l > 17) {
    lc = lret + 2 * ls + lm + data[l];
    hc = hret + 2 * hs + hm + data[h];
    if (lc + hret <= hc + lret) {
      lm += data[l];
      ls += lm;
      lret = lc;
      ++l;
    } else {
      hm += data[h];
      hs += hm;
      hret = hc;
      --h;
    }
  }
  return lret + hret;
}

int main() {
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");
    int n, x;
    fin >> n;
    vector<int> hills(101, 0);
    for (int i = 0; i < n; ++i) {
      fin >> x;
      ++hills[x];
    }
    fout << solve(hills) << endl;
    return 0;
}
