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

void find_primes(bool *primes, int n) {
  for (int i = 2; i * i <= n; ++i) {
    if (!primes[i]) continue;
    for (int j = i * i; j <= n; j += i) {
      if (primes[j]) primes[j] = false;
    } 
  }
}

bool is_palindromes(int n) {
  int b = 1;
  while(n / b >= 10) {
    b *= 10;
  }
  while (n) {
    if (n / b != n % 10) return false;
    n -= b * (n / b);
    n /= 10;
    b /= 100;
  }
  return true;
}

int main() {
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");
    int a, b;
    fin >> a >> b;
    bool *primes = new bool[b + 1];
    memset(primes, -1, sizeof(bool) * (b + 1));
    find_primes(primes, b);
    for (a = (a % 2 == 0 ? a + 1 : a); a <= b; a += 2) {
     // if (primes[a]) {
     //   cout << "a: " << a << " " << is_palindromes(a) << endl;
     // }
     if (primes[a] && is_palindromes(a)) fout << a << endl;
    }
    delete[] primes;
    return 0;
}
