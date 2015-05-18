/*
ID: disylh2
PROG: frac1
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

int gcd(int a, int b) {
  while (b) {
    swap(a, b);
    b %= a;
  }
  return a;
}

int comp(int an, int ad, int bn, int bd) {
  if (ad != bd) {
    an *= bd;
    bn *= ad;
    ad = bd = ad * bd;
  }
  return an == bn ? 0 : (an < bn) ? -1 : 1;
}
/*
0/5 1/5 2/5 3/5 4/5 
0/4 1/4 2/4 3/4 
0/3 1/3 2/3
0/2 1/2
0/1 
*/

class Comparor {
 public:
  bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
    return comp(p1.first, p1.second, p2.first, p2.second) > 0;
  }
};

void solve(int n, ofstream &fout) {
  vector<int> m(n + 1, 1);
  priority_queue<pair<int, int>, vector<pair<int, int> >, Comparor> q;
  for (int i = 1; i < n; ++i) {
    q.push({1, i + 1});
  }
  pair<int, int> last({0, 1}), curr;
  int g;
  fout << "0/1" << endl;
  while (!q.empty()) {
    curr = q.top();
    q.pop();
    if (Comparor()(curr, last)) {
     g = gcd(curr.first, curr.second);
     fout << curr.first / g << "/" << curr.second / g << endl;
     last = curr;
    }
    ++curr.first;
    if (curr.first != curr.second) {
      q.push(curr);
    }
  }
  fout << "1/1" << endl;
}

int main() {
    ofstream fout ("frac1.out");
    ifstream fin ("frac1.in");
    int n;
    fin >> n;
    fin.close();
    solve(n, fout);
    fout.close();
    return 0;
}
