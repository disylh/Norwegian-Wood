/*
ID: disylh2
PROG: maze1
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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int solve(vector<vector<char> > &m, int w,
          int h, vector<pair<int, int> > &exits) {
  queue<int> q;
  vector<bool> v(w * h, false);
  vector<int> dist(w * h, INT_MAX);
  int x, y;
  for (auto &e : exits) {
    fill_n(v.begin(), w * h, false);
    q.push(e.first * w + e.second);
    v[e.first * w + e.second] = true;
    dist[e.first * w + e.second] = 1;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      y = curr / w;
      x = curr % w;
      for (int i = 0, ny = 0, nx = 0; i < 4; ++i) {
        ny = y + dy[i];
        nx = x + dx[i];
        if (ny < 0 || ny >= h || nx < 0 || nx >= w ||
            m[y * 2 + 1 + dy[i]][x * 2 + 1 + dx[i]] != ' ' ||
            v[ny * w + nx]) {
          continue;
        }
        dist[ny * w + nx] = min(dist[ny * w + nx], dist[y * w + x] + 1);
        v[ny * w + nx] = true;
        q.push(ny * w + nx);
      }
    }
  }
  return *max_element(dist.begin(), dist.end());
}

int main() {
  ofstream fout("maze1.out");
  ifstream fin("maze1.in");
  int w, h;
  fin >> w >> h;
  vector<vector<char> > m(2 * h + 1, vector<char>(2 * w + 1, ' '));
  vector<pair<int, int> > exits;
  fin.get();
  for (int i = 0; i < 2 * h + 1; ++i) {
    for (int j = 0; j < 2 * w + 1; ++j) {
      m[i][j] = fin.get();
      if (m[i][j] != ' ') continue;
      if (i == 0) {
        exits.push_back(pair<int, int>(0, j >> 1));
      } else if (i == 2 * h) {
        exits.push_back(pair<int, int>(h - 1, j >> 1));
      } else if (j == 0) {
        exits.push_back(pair<int, int>(i >> 1, 0));
      } else if (j == 2 * w) {
        exits.push_back(pair<int, int>(i >> 1, w - 1));
      }
    }
    fin.get();
  }
  fin.close();
  fout << solve(m, w, h, exits) << endl;
  fout.close();
  return 0;
}
