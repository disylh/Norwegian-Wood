/*
ID: disylh2
PROG: milk3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void solve(int x, int y, int z, int a, int b, int c, vector<bool> &cache, vector<bool> &res)  {
  int curr = y + z * (b + 1);
  if (cache[curr]) return;
  cache[curr] = true;
  if (x == 0) {
    res[z] = true;
  }
  if (x != 0) {
    x > (b - y) ? solve(x - b + y, b, z, a, b, c, cache, res)
                : solve(0, y + x, z, a, b, c, cache, res);
    x > (c - z) ? solve(x - c + z, y, c, a, b, c, cache, res)
                : solve(0, y, z + x, a, b, c, cache, res);
  }
  if (y != 0) {
    y > (a - x) ? solve(a, y - a + x, z, a, b, c, cache, res)
                : solve(y + x, 0, z, a, b, c, cache, res);
    y > (c - z) ? solve(x, y - c + z, c, a, b, c, cache, res)
                : solve(x, 0, y + z, a, b, c, cache, res);
  }
  if (z != 0) {
    z > (b - y) ? solve(x, b, z - b + y, a, b, c, cache, res)
                : solve(x, y + z, 0, a, b, c, cache, res);
    z > (a - x) ? solve(a, y, z - a + x, a, b, c, cache, res)
                : solve(z + x, y, 0, a, b, c, cache, res);
  }
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");
    int a, b, c;
    fin >> a >> b >> c;
    vector<bool> cache((b + 1) * (c + 1), false),
        res(c + 1, false);
    solve(0, 0, c, a, b, c, cache, res);
    string ret;
    for (int i = 0, n = res.size(); i < n; ++i) {
      if (res[i]) {
        ret += to_string(i);
        ret += ' ';
      }
    }
    ret.pop_back();
    fout << ret << endl;
    return 0;
}
