/*
ID: disylh2
PROG: fact4
LANG: C++11
*/
#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T, typename TT>
ostream &operator<<(ostream &s, pair<T, TT> t) {
  return s << "(" << t.first << "," << t.second << ")";
}
template <typename T>
ostream &operator<<(ostream &s, vector<T> t) {
  for (int i = 0; i < t.size(); ++i) s << t[i] << " ";
  return s;
}

int solve(int n) {
   int x = 1, two = 0;
   for (int i = 2, curr = 0; i <= n; ++i) {
     curr = i;
     while (curr % 2 == 0) {
       ++two;
       curr /= 2;
     }
     while (curr % 5 == 0) {
       --two;
       curr /= 5;
     }
     x = x * curr % 10;
   }
   for (int i = 0; i < two; ++i) {
     x = x * 2 % 10;
   }
   return x;
}

int main() {
  ofstream fout("fact4.out");
  ifstream fin("fact4.in");
  int n;
  fin >> n;
  fin.close();
  fout << solve(n) << endl;
  fout.close();
  return 0;
}
