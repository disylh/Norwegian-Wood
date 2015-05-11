/*
ID: disylh2
PROG: dualpal
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

string convert(int n, int base) {
  int rmd = 0;
  string ret;
  while(n) {
    rmd = n % base;
    if (rmd >= 10) {
      ret += rmd - 10 + 'A';
    } else {
      ret += rmd + '0';
    }
    n = n / base;
  }
  return string(ret.rbegin(), ret.rend());
}

bool ispalindrome(string &&str) {
  for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) return false;
  }
  return true;
}

void solve(ofstream &fout, int n, int s) {
  for (int i = s + 1, c = 0, c2 = 0; c < n; ++i) {
    c2 = 0;
    for (int b = 2; b <= 10 && c2 != 2; ++b) {
      if (ispalindrome(convert(i, b))) {
        ++c2;
      }
      if (c2 == 2) {
        fout << i << endl;
        ++c;
      }
    }
  }
}

using namespace std;
int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");
    int n, s;
    fin >> n >> s;
    solve(fout, n, s);
    return 0;
}
