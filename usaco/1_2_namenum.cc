/*
ID: disylh2
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <initializer_list>

using namespace std;

vector<vector<char> > m({{},
                         {},
                         {'A', 'B', 'C'},
                         {'D', 'E', 'F'},
                         {'G', 'H', 'I'},
                         {'J', 'K', 'L'},
                         {'M', 'N', 'O'},
                         {'P', 'R', 'S'},
                         {'T', 'U', 'V'},
                         {'W', 'X', 'Y'}});

pair<int, bool> solve(const string &num, string &name, int i, ifstream &dict, string &word, ofstream &fout) {
  pair<int, bool> ret(0, false), res;
  if (num.size() == i) {
    int comp = 0;
    do {
      comp = word.compare(name);
      if (comp == 0) {
        fout << name << endl;
        ret.first = 1;
        return ret;
      } else if (comp > 0) {
        break;
      }
    } while (dict >> word); 
    return ret;
  }
  int d = num[i] - '0';
  if (m[d].size() == 0) {
    ret.second = true;
  }
  for (int t = 0, n = m[d].size(); t < n; ++t) {
    name[i] = m[d][t];
    res = solve(num, name, i + 1, dict, word, fout); 
    if (res.second) {
      return res;
    }
    ret.first += res.first;
  }
  return ret;
}

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream fdict ("dict.txt");
    string num;
    fin >> num;
    int n = num.size(); 
    string name(n, '.'), word;
    auto res = solve(num, name, 0, fdict, word, fout);
    if (res.first == 0) {
      fout << "NONE" << endl;
    }
    return 0;
}
