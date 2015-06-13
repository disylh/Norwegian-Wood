/*
ID: disylh2
PROG: fracdec
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
#include <unordered_map>

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

string solve(int n, int d) { 
  string ret = to_string(n / d); 
  ret += '.';
  if ((n %= d) == 0) {
    return ret + "0";
  }
  vector<int> m(100000, -1);
  int ml = 0;
  m[n] = ml++;
  n *= 10;
  while (true) {
    ret += n / d + '0';
    if (n % d == 0) {
      return ret;
    } else if (n > d) {
      n %= d;
    }
    if (m[n] != -1) {
      return ret.substr(0, ret.size() - (ml - m[n])) + "(" +
             ret.substr(ret.size() - (ml - m[n])) + ")";
    }
    m[n] = ml++;
    n *= 10;
  }
  return ret;
}

int main() {
  ofstream fout("fracdec.out");
  ifstream fin("fracdec.in");
  int n, d;
  fin >> n >> d;
  fin.close();
  string res = solve(n, d);
  for (int i = 1, e = res.size(); i <= e; ++i) {
    fout << res[i-1];
    if (i % 76 == 0) {
      fout << endl;
    }
  }
  fout << endl;
  fout.close();
  return 0;
}
