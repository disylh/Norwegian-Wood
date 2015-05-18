/*
ID: disylh2
PROG: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int solve(vector<vector<int> > &tri) {
  int n = tri.size();
  vector<int> dp(tri[n - 1]);
  for (int i = n - 2; i >= 0; --i) {
    for (int j = 0; j <= i; ++j) {
      dp[j] = tri[i][j] + max(dp[j], dp[j+1]);
    }
  } 
  return dp[0];
}

int main() {
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");
    int r, x;
    fin >> r;
    vector<vector<int> > tri(r, vector<int>(r, 0));
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j <= i; ++j) {
        fin >> tri[i][j];
      }
    }
    fout << solve(tri) << endl;
    return 0;
}
