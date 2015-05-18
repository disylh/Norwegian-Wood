/*
ID: disylh2
PROG: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

bool is_prime(int n) {
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

int next_palindrome(int n) {
  int lb = 1, hb = 1, l, h;
  bool carry = false;
  while (n / hb >= 10) hb *= 10;
  while (hb >= lb) {
    l = n / lb % 10;
    h = n / hb % 10;
    if ((carry && l < h) || (!carry && l <= h)) {
      carry = false;
      n += (h - l) * lb;
    } else {
      carry = true;
      if (n % (hb * 10) / lb + 1 == hb / lb * 10) {
        return n + lb + lb / 10;
      }
      if (hb == lb) return n + hb;
      if (hb == lb * 10) return n + hb - (l - h - 1) * lb;
      n -= (l - h) * lb;
    }
    hb /= 10;
    lb *= 10;
  }
  return n;
}

void solve(int a, int b, ofstream &fout) {
  while ((a = next_palindrome(a)) <= b) {
    if (is_prime(a)) fout << a << endl;
    ++a;
  }
}

int main() {
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");
    int a, b;
    fin >> a >> b;
    solve(a, b, fout);
    return 0;
}
