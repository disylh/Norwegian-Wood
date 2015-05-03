#include<vector>
#include<queue>
#include<iostream>

using namespace std;

class Comp {
 public:
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
    return a.first > b.first;
  }
};
int second_shortest(const vector<vector<pair<int, int> > > &g, int s, int t) {
  int n = g.size();
  vector<pair<int, int> > dp(n, make_pair(INT_MAX, INT_MAX));
  priority_queue<pair<int, int>, vector<pair<int, int> >, Comp> q;
  dp[1].first = 0;
  q.push(make_pair(0, 1));
  while (!q.empty()) {
    pair<int,int> curr = q.top();
    q.pop();
    if (dp[curr.second].first < curr.first) continue;
    for (int i = 0, n = g[curr.second].size(); i < n; ++i) {
      const pair<int,int> &edge = g[curr.second][i];
      int val = curr.first + edge.second;
      if (dp[edge.first].first > val) {
        swap(dp[edge.first].first, dp[edge.first].second);
        dp[edge.first].first = val;
        q.push(make_pair(dp[edge.first].first, edge.first));
      } else if (dp[edge.first].first != val && dp[edge.first].second > val) {
        dp[edge.first].second = val;
      }
      val = dp[edge.first].first + edge.second;
      if (dp[curr.second].first != val && dp[curr.second].second > val) {
        dp[curr.second].second = val;
      } else if (dp[edge.first].second != INT_MAX) {
        val = dp[edge.first].second + edge.second;
        if (dp[curr.second].first != val && dp[curr.second].second > val) {
          dp[curr.second].second = val;
        }
      }
    }
  }
  return dp[n-1].second;
}
int main() {
  int n, r;
  cin >> n >> r;
  vector<vector<pair<int, int> > > g(n + 1, vector<pair<int, int> > ());
  for (int i = 0, a = 0, b = 0, w = 0; i < r; ++i) {
    cin >> a >> b >> w;
    g[a].push_back(make_pair(b, w));
    g[b].push_back(make_pair(a, w));
  }
  cout << second_shortest(g, 1, n) << endl;
}
