/*
ID: disylh2
PROG: humble
LANG: C++11
*/
#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
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

int solve(vector<int> &p, int n) {
  vector<int> hm(n + 1, 0), pindex(p.size(), 0);
  int hsz = 0, mni = 0;
  hm[hsz++] = 1;
  for (; hsz < n + 1; ++hsz) {
    mni = -1;
    for (int i = 0, pn = p.size(); i < pn; ++i) {
      while ((double)p[i] * hm[pindex[i]] <= hm[hsz - 1]) {
        ++pindex[i];
      }
      if (mni == -1 ||
          (double)p[mni] * hm[pindex[mni]] > p[i] * hm[pindex[i]]) {
        mni = i;
      }
    }
    hm[hsz] = p[mni] * hm[pindex[mni]++];
  }
  return hm[n];
}

int solve_old(vector<int> &p, int n) {
  int curr = 1, temp = 0, bound = 0;
  set<int> st(p.begin(), p.end());
  set<int>::iterator it;
  while (n--) {
    it = st.begin();
    curr = *it;
    st.erase(it);
    bound = INT_MAX / curr;
    for (auto &val : p) {
      if (bound < val) {
        continue; 
      }
      temp = curr * val;
      it = st.find(temp);
      if (it != st.end()) { 
        continue;
      }
      if (st.size() > n) {
        it = st.end();
        --it;
        if (*it < temp) {
          continue;
        }
        st.erase(it);
      }
      st.emplace(temp);
    }
  }
  return curr;
}

int main() {
  ofstream fout("humble.out");
  ifstream fin("humble.in");
  int k, n; 
  fin >> k >> n;
  vector<int> p(k, 0);
  for (int i = 0; i < k; ++i) {
    fin >> p[i];
  }
  fin.close();
  fout << solve(p, n) << endl;
  fout.close();
  return 0;
}
