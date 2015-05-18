/*
ID: disylh2
PROG: ariprog
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void solve(int n, int m, ofstream &fout) {
  int mm = m * m * 2;
  vector<bool> bsq(mm + 1, false);
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= m; ++j) {
      bsq[i * i + j * j] = true;
    }
  }
  bool none = true;
  for (int i = 1, in = mm / (n - 1); i <= in; ++i) {
    for (int j = 0, jn = mm - i * (n - 1); j <= jn ; ++j) {
      bool good = true;
      for (int k = 0, curr = j; k < n; ++k, curr += i) {
        if (!bsq[curr]) {
  //        cout << "false at " << curr << endl;
          good = false;
          break;
        }
      }
   //   cout << j << " " << i << " " << good << endl;
      if (good) {
        none = false;
        fout << j << " " << i << endl;
      }
    }
  }
  if (none) {
    fout << "NONE" << endl;
  }
}

int main() {
    ofstream fout ("ariprog.out");
    ifstream fin ("ariprog.in");
    int n, m;
    fin >> n >> m;
    solve(n, m, fout);
    return 0;
}
