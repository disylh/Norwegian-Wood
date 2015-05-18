/*
ID: disylh2
PROG: sprime
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
  if (n == 2) return true;
  if (n == 1 || n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void dfs(int curr, int n, ofstream &fout) {
  if (n == 0) {
    fout << curr << endl;
    return;
  }
  curr *= 10;
  --n;
  if (is_prime(curr + 1)) {
    dfs(curr + 1, n, fout);
  }
  if (is_prime(curr + 3)) {
    dfs(curr + 3, n, fout);
  }
  if (is_prime(curr + 7)) {
    dfs(curr + 7, n, fout);
  }
  if (is_prime(curr + 9)) {
    dfs(curr + 9, n, fout);
  }
}

int main() {
    ofstream fout ("sprime.out");
    ifstream fin ("sprime.in");
    int n, b = 1;
    fin >> n;
    --n;
    dfs(2, n, fout);
    dfs(3, n, fout);
    dfs(5, n, fout);
    dfs(7, n, fout);
    return 0;
}
