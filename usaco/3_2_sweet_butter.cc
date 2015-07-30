/*
ID: disylh2
PROG: butter
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

int dijkstra(vector<int> &cp, vector<vector<pair<int, int> > > &g, int p, int curr) {
  vector<int> dist(p + 1, INT_MAX);
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push(make_pair(0, curr));
  while (!pq.empty()) {
    pair<int, int> edge = pq.top();
    pq.pop();
    if (dist[edge.second] > edge.first) {
      dist[edge.second] = edge.first;
      for (int i = 0, in = g[edge.second].size(); i < in; ++i) {
        if (dist[g[edge.second][i].second] == INT_MAX) {
          pq.push(make_pair(g[edge.second][i].first + edge.first, g[edge.second][i].second));
        }
      }
    }
  }
  int ret = 0;
  for (int i = 1; i <= p; ++i) {
    if (cp[i] > 0 && dist[i] == INT_MAX) {
      return INT_MAX;
    }
    ret += cp[i] * dist[i];
  }
  return ret;
}

int solve(vector<int> &cp, vector<vector<pair<int, int> > > &g, int p) {
  int ret = INT_MAX;
  for (int i = 1; i <= p; ++i) {
    ret = min(ret, dijkstra(cp, g, p, i));
  }
  return ret;
}

int main() {
  ofstream fout("butter.out");
  ifstream fin("butter.in");
  int n, p, c;
  fin >> n >> p >> c;
  vector<int> cp(p + 1, 0);
  vector<vector<pair<int, int> > > graph(p + 1, vector<pair<int, int> >());
  for (int i = 0, temp; i < n; ++i) {
    fin >> temp;
    ++cp[temp];
  }
  for (int i = 0, p1, p2, w; i < c; ++i) {
    fin >> p1 >> p2 >> w;
    graph[p1].push_back(make_pair(w, p2));
    graph[p2].push_back(make_pair(w, p1));
  }
  fin.close();
  fout << solve(cp, graph, p) << endl;
  fout.close();
  return 0;
}

