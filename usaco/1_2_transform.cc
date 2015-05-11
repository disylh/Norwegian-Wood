/*
ID: disylh2
PROG: transform
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void print(const vector<bool> &p, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << p[i * n + j];
    }
    cout << endl;
  }
  cout << endl;
}

bool is_equal(const vector<bool> &before, const vector<bool> &after) {
  for (int i = 0, n = before.size(); i < n; ++i) {
    if (before[i] != after[i]) return false;
  }
  return true;
}

void rotate_90(int n, vector<bool> *p) {
  bool temp;
  for (int i = 0, ei = (n + 1) >> 1; i < ei; ++i) {
    for (int j = 0, ej = n >> 1; j < ej; ++j) {
      temp = p->at(j * n + n - 1 - i);
      p->at(j * n + n - 1 - i) = p->at(i * n + j);
      p->at(i * n + j) = p->at((n - 1 - j) * n + i);
      p->at((n - 1 - j) * n + i) = p->at((n - 1 - i) * n + n - 1 - j);
      p->at((n - 1 - i) * n + n - 1 - j) = temp;
    }
  }
}

void reflect(int n, vector<bool> *p) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0, nj = n >> 1; j < nj; ++j) {
      swap(p->at(i * n + j), p->at(i * n + n - 1 - j));
    }
  }
}

int rotated(vector<bool> &before, vector<bool> &after, int n) {
  rotate_90(n, &before);
  int ret = 0;
  if (is_equal(before, after)) {
    ret = 1;
  }
  rotate_90(n, &before);
  if (ret == 0 && is_equal(before, after)) {
    ret = 2;
  }
  rotate_90(n, &before);
  if (ret == 0 && is_equal(before, after)) {
    ret = 3;
  }
  rotate_90(n, &before);
  return ret;
}

int solve(vector<bool> &before, vector<bool> &after, int n) {
  int r = rotated(before, after, n);
  if (r) return r;
  reflect(n, &before);
  if (is_equal(before, after)) {
    return 4;
  }
  r = rotated(before, after, n);
  if (r) return 5;
  reflect(n, &before);
  if (is_equal(before, after)) {
    return 6;
  }
  return 7;
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    int n;
    char c;
    fin >> n;
    vector<bool> before(n * n, false), after(n * n, false);
    for (int i = 0, e = n * n; i < e; ++i) {
      fin >> c;
      if (c == '@') {
        before[i] = true;
      }
    }
    for (int i = 0, e = n * n; i < e; ++i) {
      fin >> c;
      if (c == '@') {
        after[i] = true;
      }
    }
    fout << solve(before, after, n) << endl;
    return 0;
}
