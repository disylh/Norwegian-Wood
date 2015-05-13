/*
ID: disylh2
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool isvalid(const vector<int> &data, int x, int l) {
  int n = data.size(), ll = 0, t;
  bool found;
  while (x) {
    t = x % 10;
    x /= 10;
    ++ll;
    found = false;
    for (int i = 0; i < n; ++i) {
      if (data[i] == t) {
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  return l == ll;
}

int solve(const vector<int> &data) {
  int n = data.size(), ret = 0;
  for (int a = 0, x, y; a < n; ++a) {
    for (int b = 0; b < n; ++b) {
      for (int c = 0; c < n; ++c) {
        for (int d = 0; d < n; ++d) {
          for (int e = 0; e < n; ++e) {
            x = data[a] * 100 + data[b] * 10 + data[c];
            y = data[d] * 10 + data[e];
            if (isvalid(data, x * data[e], 3) &&
                isvalid(data, x * data[d], 3) &&
                isvalid(data, x * y, 4)) {
              ++ret;
            }
          }
        }
      }
    }
  }
  return ret;
}

int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");
    int n, d;
    fin >> n;
    vector<int> data;
    for (int i = 0; i < n; ++i) {
      fin >> d;
      data.push_back(d);
    }
    fout << solve(data) << endl;
    return 0;
}
