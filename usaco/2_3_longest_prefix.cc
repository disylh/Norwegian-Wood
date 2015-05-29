/*
ID: disylh2
PROG: prefix
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
#include <memory>

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

class TrieNode {
  public:
    char c_;
    bool isw_;
    unique_ptr<TrieNode> children_[26];
    TrieNode(char c): c_(c), isw_(false) { }
};

class Trie {
  public:
    Trie(): root_(new TrieNode('.')) { }
    void add(const string &str) {
      TrieNode *curr = root_.get();
      for (int i = 0, n = str.size(); i < n; ++i) {
        char c = str[i] - 'A';
        if (curr->children_[c] == nullptr) {
          curr->children_[c] = unique_ptr<TrieNode>(new TrieNode(c));
        }
        curr = curr->children_[c].get();
        if (i == n - 1) {
          curr->isw_ = true;
        }
      }
    }
    TrieNode *get_root() {
      return root_.get();
    }
  private:
    unique_ptr<TrieNode> root_;
};

int main() {
  ifstream fin("prefix.in");
  string str;
  Trie t;
  fin >> str;
  while (str != ".") {
    t.add(str);
    fin >> str;
  }
  int fpos = 0, ret = 0, cnt = 0, bhead = 0, btail = bhead;
  vector<bool> f(11, false);
  vector<char> buff(200, 0);
  f[0] = true;
  while (true) {
    if ((btail - bhead + 200) % 200 < 20 && (fin >> str)) {
      for (auto &c : str) {
        buff[btail] = c;
        btail = (btail + 1) % 200;
      }
    }
    TrieNode *tcurr = t.get_root(), *tnext = nullptr;
    for (int i = 1; (fpos + i) % 11 != fpos && (bhead + i - 1) % 200 != btail; ++i) {
      char c = buff[(bhead + i - 1) % 200] - 'A';
      if (tcurr->children_[c] != nullptr) {
        tnext = tcurr->children_[c].get();
        if (tnext->isw_) {
          f[(fpos + i) % 11] = true;
          ret = max(ret, cnt + i);
        }
        tcurr = tnext;
      } else {
        break;
      }
    }
    f[fpos] = false;
    bool stop = true;
    for (int i = 1; (fpos + i) % 11 != fpos && (bhead + i) % 200 != btail;
         ++i) {
      if (f[(fpos + i) % 11]) {
        stop = false;
        cnt += i;
        fpos = (fpos + i) % 11;
        bhead = (bhead + i) % 200;
        break;
      }
    }
    if (stop) break;
  }
  fin.close();
  ofstream fout("prefix.out");
  fout << ret << endl;
  fout.close();
  return 0;
}
