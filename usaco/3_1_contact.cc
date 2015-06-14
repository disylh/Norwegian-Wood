/*
ID: disylh2
PROG: contact
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

string to_binary_str(int n, int len) {
  string ret;
  for (int i = 0; i < len; ++i) {
    ret += (n >> i) % 2 ? '1' : '0';
  }
  return ret;
}

void process(vector<bool> &pat, vector<int> &freq, int len) {
  int pn = pat.size(), curr = 0;
  if (pn < len) return;
  for (int i = 0; i < len; ++i) {
    if (pat[i]) {
      curr |= 1 << i;
    }
  }
  ++freq[curr];
  for (int i = len; i < pn; ++i) {
    curr >>= 1;
    if (pat[i]) {
      curr |= 1 << (len - 1);
    }
    ++freq[curr];
  }
}

void solve(int a, int b, int n, vector<bool> &pat, ofstream &fout) {
  int pn = pat.size();
  vector<int> freq(1 << b, 0);
  vector<tuple<int, int, string> > res;
  for (int i = a; i <= b; ++i) {
    fill_n(freq.begin(), 1 << i, 0);
    process(pat, freq, i);
    for (int j = 0, jn = 1 << i; j < jn; ++j) {
      if (freq[j] != 0) {
        res.push_back(make_tuple(-freq[j], i, to_binary_str(j, i)));
      }
    }
  }
  sort(res.begin(), res.end());
  for (int i = 0, in = res.size(), pre = 1, prelen = 0, count = 0; i < in; ++i) {
    if (get<0>(res[i]) != pre) {
      ++count;
      if (count == n + 1) break;
      if (pre != 1) {
        fout << endl;
      }
      pre = get<0>(res[i]);
      prelen = 0;
      fout << -pre << endl;
    } else if (prelen % 6) {
      fout << " ";
    } else {
      fout << endl;
    }
    ++prelen;
    fout << get<2>(res[i]);
  }
  fout << endl;
}

int main() {
  ofstream fout("contact.out");
  ifstream fin("contact.in");
  int a, b, n;
  char c;
  fin >> a >> b >> n;
  fin.get();
  vector<bool> pat;
  while (fin.get(c)) {
    if (c == '1') {
      pat.push_back(true);
    } else if (c == '0') {
      pat.push_back(false);
    }
  }
  fin.close();
  solve(a, b, n, pat, fout);
  fout.close();
  return 0;
}
