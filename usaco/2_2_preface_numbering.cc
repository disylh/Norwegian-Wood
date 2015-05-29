/*
ID: disylh2
PROG: preface
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>

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

int NCHAR = 7;
char charset[] = "IVXLCDM";
int valset[] = {1, 5, 10, 50, 100, 500, 1000};

void solve(int n, ofstream &fout) {
  vector<int> count(NCHAR, 0);
  for (int i = 1, temp = 0, curr = 0; i <= n; ++i) {
    curr = i;
    count[NCHAR - 1] += curr / valset[NCHAR - 1];
    curr %= valset[NCHAR - 1];
    for (int j = NCHAR - 2; j >= 0; j -= 2) {
      temp = curr / valset[j - 1];
      if (temp == 9) {
        ++count[j + 1];
        ++count[j - 1];
      } else if (temp <= 3) {
        count[j - 1] += temp;
      } else {
        ++count[j];
        count[j - 1] += abs(temp - 5);
      }
      curr %= valset[j - 1];
    }
  }
  for (int i = 0; i < NCHAR; ++i) {
    if (count[i] > 0) {
      fout << charset[i] << " " << count[i] << endl;
    }
  }
}

int main() {
  ofstream fout("preface.out");
  ifstream fin("preface.in");
  int n;
  fin >> n;
  fin.close();
  solve(n, fout);
  fout.close();
  return 0;
}
