#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
  int a;
  int b;
  int cost;
  Edge(int a, int b, int cost) : a(a), b(b), cost(cost) {}
};

class DisjointSet {
 public:
  DisjointSet(int n) : data_(vector<int>(n, -1)), rank_(vector<int>(n, 0)) {}
  int find(int x) {
    if (data_[x] == -1) {
      return x;
    } else {
      return data_[x] = find(data_[x]);
    }
  }
  void merge(int x, int y) {
    int xroot = find(x), yroot = find(y);
    if (xroot == yroot) {
      return;
    }
    if (rank_[xroot] > rank_[yroot]) {
      data_[yroot] = xroot;
    } else if (rank_[xroot] < rank_[yroot]) {
      data_[xroot] = yroot;
    } else {
      data_[yroot] = xroot;
      ++rank_[xroot];
    }
  }

 private:
  vector<int> data_;
  vector<int> rank_;
};

bool comp(const Edge &e1, const Edge &e2) { return e1.cost > e2.cost; }

int solve_kruskal(int n, vector<Edge> *edges) {
  DisjointSet ds(n);
  sort(edges->begin(), edges->end(), comp);
  int ret = 0;
  for (int i = 0, en = edges->size(); i < en; ++i) {
    Edge &curr = edges->at(i);
    if (ds.find(curr.a) != ds.find(curr.b)) {
      ret += curr.cost;
      ds.merge(curr.a, curr.b);
    }
  }
  return ret;
}

class PairComparor {
 public:
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
    return a.second < b.second;
  }
};

int solve_prim(const vector<vector<pair<int, int> > > &g, int n) {
  vector<bool> used(n, false);
  priority_queue<pair<int, int>, vector<pair<int, int> >, PairComparor> q;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    if (used[i]) continue;
    q.push(make_pair(i, 0));
    while (!q.empty()) {
      const pair<int, int> curr = q.top();
      q.pop();
      if (used[curr.first]) continue;
      used[curr.first] = true;
      ret += curr.second;
      for (int j = 0, ce = g[curr.first].size(); j < ce; ++j) {
        const pair<int, int> &neighbor = g[curr.first][j];
        if (!used[neighbor.first]) {
          q.push(neighbor);
        }
      }
    }
  }
  return ret;
}

int main() {
  int c, n, m, r, x, y, d;
  cin >> c;
  for (int i = 0; i < c; ++i) {
    scanf("%d %d %d", &n, &m, &r);
    vector<vector<pair<int, int> > > g(n + m, vector<pair<int, int> >());
    // vector<Edge> edges;
    for (int j = 0; j < r; ++j) {
      // cin >> x >> y >> d;
      scanf("%d %d %d", &x, &y, &d);
      // edges.push_back(Edge(x, y + n, d));
      g[x].push_back(make_pair(y + n, d));
      g[y + n].push_back(make_pair(x, d));
    }
    // printf("%d\n", (m + n) * 10000 - solve_kruskal(m + n, &edges));
    printf("%d\n", (m + n) * 10000 - solve_prim(g, m + n));
  }
}
