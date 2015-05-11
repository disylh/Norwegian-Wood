/*
ID: disylh2
PROG: palsquare
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

bool ispalindrome(string &str) {
  for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) return false;
  }
  return true;
}

void solve(ofstream &fout, int b) {
  for (int i = 1; i <= 300; ++i) {
    string sq = convert(i * i, b);
    if (ispalindrome(sq)) {
      fout << convert(i, b) << " " << sq << endl;
    }
  }
}

using namespace std;
int main() {
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");
    int b;
    fin >> b;
    solve(fout, b);
    return 0;
}
