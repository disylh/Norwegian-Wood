/*
ID: disylh2
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
    int np, curr, n, each;
    string name, temp; 
    vector<pair<string, int> > v;
    unordered_map<string, int> m;
    fin >> np;
    for (int i = 0; i < np; ++i) {
      fin >> name;
      v.push_back(make_pair(name, 0));
      m[name] = i;
    }
    while (fin >> name) {
      fin >> curr >> n;
      v[m[name]].second -= n == 0 ? 0 : curr - curr % n;
      each = n == 0 ? 0 : curr / n;
      for (int i = 0; i < n; ++i) {
        fin >> temp;
        v[m[temp]].second += each;
      }
    }
    for (int i = 0; i < np; ++i) {
      fout << v[i].first << " " << v[i].second << endl;
    }
    return 0;
}
