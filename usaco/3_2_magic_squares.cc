/*
ID: disylh2
PROG: msquare
LANG: C++11
*/
#include <cstring>
#include <climits>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iterator>
#include <functional>

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

int factorial(int n) {
  int ret = 1;
  for (int i = 2; i <= n; ++i) {
    ret *= i;
  }
  return ret;
}

int get_hash(vector<int> vec) {
  int ret = 0;
  for (int n = vec.size(), i = n - 2, k = 0, c = 1; i >= 0; --i) {
    k = 0;
    for (int j = i + 1; j < n; ++j) {
      if (vec[i] > vec[j]) ++k;
    }
    ret += k * c;
    c *= n - i;
  }
  return ret;
}

vector<int> unhash(int n, int base) {
  vector<int> ret(base, 0), used(base, false);
  int c = factorial(base - 1);
  for (int i = 0, curr = 0, val = 1; i < base; ++i) {
    curr = n / c;
    val = 1;
    for (; val <= base; ++val) {
      if (!used[val - 1]) {
        if (curr == 0) {
          used[val - 1] = true;
          break;
        }
        --curr;
      }
    }
    ret[i] = val;
    n %= c;
    if (i != base - 1) c /= base - 1 - i;
  }
  return ret;
}

int a(int n, int base) {
  vector<int> sq = unhash(n, base);
//  cout << "a before " << sq << endl;
  for (int l = 0, r = sq.size() - 1; l < r; ++l, --r) {
    swap(sq[l], sq[r]);
  }
//  cout << "a after " << sq << endl;
  return get_hash(sq);
}

int b(int n, int base) {
  vector<int> sq = unhash(n, base);
//  cout << "b before " << sq << endl;
  int temp = sq[base / 2 - 1];
  for (int i = base / 2 - 1; i > 0; --i) {
    sq[i] = sq[i - 1];
  }
  sq[0] = temp; 
  temp = sq[base / 2];
  for (int i = base / 2; i < base - 1; ++i) {
    sq[i] = sq[i + 1];
  }
  sq[base - 1] = temp;
//  cout << "b after " << sq << endl;
  return get_hash(sq);
}

int c(int n, int base) {
  vector<int> sq = unhash(n, base);
//  cout << "c before " << sq << endl;
  int temp = sq[1];
  sq[1] = sq[6];
  sq[6] = sq[5];
  sq[5] = sq[2];
  sq[2] = temp;
//  cout << "c after " << sq << endl;
  return get_hash(sq);
}

vector<char> gen_result(vector<pair<char, int> > &path, int src, int tgt) {
  vector<char> ret;
  cout << "src " << src << " tgt " << tgt << endl;
  while (src != tgt && path[tgt].second != -1) {
    ret.push_back(path[tgt].first);
    tgt = path[tgt].second;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

vector<pair<char, function<int(int, int)> > > trans = {
  make_pair('A', a), make_pair('B', b), make_pair('C', c)
};

void solve(vector<int> &target, ofstream &fout) {
  int base = target.size(), sz = factorial(base), s = 0, t = get_hash(target);
  cout << target << endl;
  vector<pair<char, int> > path(sz, make_pair('.', -1));
  queue<int> q;
  q.push(s);
  path[s].second = s;
  for (int curr = 0, temp = 0; !q.empty();) {
    curr = q.front();
    q.pop();
    if (curr == t) break;
    for (const auto &t : trans) {
      temp = t.second(curr, base);
      if (path[temp].second == -1) {
        path[temp].first = t.first;
        path[temp].second = curr;
        q.push(temp);
      }
    }
  }
  auto res = gen_result(path, s, t);
  fout << res.size() << endl;
  if (res.size() != 0) {
    for (int i = 0, in = res.size(); i < in; ++i) {
      fout << res[i];
      if (i != in - 1 && (i + 1) % 60 == 0) {
        fout << endl;
      }
    }
  }
  fout << endl;
}

int main() {
  ofstream fout("msquare.out");
  ifstream fin("msquare.in");
  vector<int> target(8, 0);
  for (int i = 0, n = target.size(); i < n; ++i) {
    fin >> target[i];
  }
  fin.close();
  solve(target, fout);
  fout.close();
  return 0;
}
