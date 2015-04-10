
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cmath>
#include <ctime>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include <utility>
#include <functional>
#include <stdexcept>
#include <iomanip>
#include <numeric>


#define s(n) scanf("%d", &n)
#define sc(n) scanf("%c", &n)
#define sl(n) scanf("%lld", &n)
#define sf(n) scanf("%lf", &n)
#define ss(n) scanf("%s", n)

#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef vector<bool> VB;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

template <typename T, typename TT>
ostream &operator<<(ostream &s, pair<T, TT> t) {
  return s << "(" << t.first << "," << t.second << ")";
}
template <typename T>
ostream &operator<<(ostream &s, vector<T> t) {
  for (int i = 0; i < t.size(); ++i) s << t[i] << " ";
  return s;
}

double get_sec(clock_t t) { return static_cast<double>(t) / CLOCKS_PER_SEC;}
double get_ms(clock_t t) { return get_sec(t) * 1000; }

class Egalitarianism {
public:
  int maxDifference(vector <string> isFriend, int d) {
    n_ = isFriend.size();
    VB visited(n_, false);
    dfs(isFriend, visited, 0);
    for (int i = 0; i < n_; ++i) {
      if (!visited[i]) {
        return -1;
      }
    }
    int ret = 0;
    /*
    for (int i = 0; i < n_; ++i) {
      ret = max(ret, bfs(isFriend, visited, i));
    }
    */
    ret = floyd_warshall(isFriend);
    return ret * d;
  }
  void dfs(const VS &isFriend, VB &visited, int i) {
    if (visited[i]) {
      return;
    }
    visited[i] = true;
    for (int j = 0; j < n_; ++j) {
      if (isFriend[i][j] == 'Y') {
        dfs(isFriend, visited, j);
      }
    }
  }
  int bfs(const VS &isFriend, VB &visited, int i) {
    fill_n(visited.begin(), n_, false);
    queue<int> q[2];
    int ret = -1, curr = 0, temp = 0;
    bool flag = false;
    q[curr].push(i);
    while (!q[curr].empty()) {
      flag = false;
      while (!q[curr].empty()) {
        temp = q[curr].front();
        q[curr].pop();
        if (!visited[temp]) {
          visited[temp] = true;
          flag = true;
          for (int j = 0; j < n_; ++j) {
            if (!visited[j] && isFriend[temp][j] == 'Y') {
              q[1-curr].push(j);
            }
          }
        }
      }
      curr = 1 - curr;
      if (flag) {
        ++ret;
      }
    }
    return ret;
  }
  int floyd_warshall(const VS &isFriend) {
    int n = isFriend.size();
    vector<vector<int> > dist(n, vector<int>(n, INT_MAX));
    int ret = 0;
    for (int i = 0; i < n - 1; ++i) {
      dist[i][i] = 0;
      for (int j = i + 1; j < n; ++j) {
        if (isFriend[i][j] == 'Y') {
          dist[i][j] = dist[j][i] = 1;
        }
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
            dist[i][j] = dist[j][i] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        ret = max(ret, dist[i][j]);
      }
    }
    return ret;
  }
private:
  int n_;
};
