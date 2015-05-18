/*
ID: disylh2
PROG: castle
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

#define NDIR 4
int dr[NDIR] = {1, 8, 4, 2};
char drn[NDIR] = {'W', 'S', 'E', 'N'};
int drx[NDIR] = {-1, 0, 1, 0};
int dry[NDIR] = {0, 1, 0, -1};

int bfs(const vector<int> &mp, int m, int n, int rid, vector<int> &modu, int curr) {
  queue<int> q;
  q.push(curr);
  modu[curr] = rid;
  int ret = 0, neb = 0;
  while (!q.empty()) {
    ++ret;
    curr = q.front();
    q.pop();
    //cout << curr << " " << mp[curr] << endl;
    for (int d = 0, nx, ny; d < NDIR; ++d) {
      if ((mp[curr] & dr[d]) == 0) {
        ny = curr / m + dry[d];
        nx = curr % m + drx[d];
        neb = ny * m + nx;
        //cout << curr << " neb  " << neb << " by " << drn[d];
        if (ny >= 0 && ny < n && nx >= 0 && nx < m && modu[neb] == -1) {
          q.push(neb);
          modu[neb] = rid;
          //cout << " push ";
        }
        //cout << endl;
      }
    }
  }
  return ret;
}

void solve(const vector<int> &mp, int m, int n, ofstream &fout) {
  int total = m * n, rn = 0, tn = m * n, rmw = 0, rmwd = 0, rmws = 0, neb = 0;
  vector<int> modu(total, -1), rs;
  for (int curr = 0; curr < total; ++curr) {
    if (modu[curr] != -1) continue;
    rs.push_back(bfs(mp, m, n, rn, modu, curr));
    ++rn;
  }
  for (int j = m - 1, curr = 0; j >= 0; --j) {
    for (int i = 0; i < n; ++i) {
      for (int d = 2; d < NDIR; ++d) {
        curr = i * m + j;
        neb = (i + dry[d]) * m + j + drx[d];
        if (i + dry[d] >= 0 && i + dry[d] < n && j + drx[d] >= 0 &&
            j + drx[d] < m && neb < total && modu[curr] != modu[neb] &&
            rmws <= rs[modu[curr]] + rs[modu[neb]]) {
          rmw = curr;
          rmws = rs[modu[curr]] + rs[modu[neb]];
          rmwd = d;
          //cout << "update removal " << rmw << " " << rmws << " " << drn[rmwd] << endl;
        }
      }
    }
  }
  //cout << modu << endl;
  //cout << rs << endl;

  fout << rn << endl;
  fout << *max_element(rs.begin(), rs.end()) << endl;
  fout << rmws << endl;
  fout << rmw / m + 1 << " " << rmw % m + 1 << " " << drn[rmwd] << endl;
}

int main() {
    ofstream fout ("castle.out");
    ifstream fin ("castle.in");
    int m, n;
    fin >> m >> n;
    vector<int> mp(m * n, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        fin >> mp[i * m + j];
      }
    }
    fin.close();
    solve(mp, m, n, fout);
    fout.close();
    return 0;
}
