/*
ID: disylh2
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int calc(const string &str) {
  int ret = 1;
  for (const auto &c : str) {
    ret = ret * (c - 'A' + 1) % 47;
  }
  return ret;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string a, b;
    fin >> a >> b;
    fout << (calc(a) == calc(b) ? "GO" : "STAY") << endl;
    return 0;
}
