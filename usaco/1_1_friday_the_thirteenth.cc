/*
ID: disylh2
PROG: friday
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>

using namespace std;

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
    int n, year = 1900, start = 0;
    bool leap = false;
    fin >> n; 
    vector<int> freq(7, 0);
    vector<int> md({31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
    while (n--) {
      if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        leap = true;
      } else {
        leap = false;
      }
      for (int i = 0; i < 12; ++i) {
        ++freq[start];
        start = (start + ((i == 1 && leap) ? 29 : md[i])) % 7;
      }
      ++year;
    }
    fout << freq[0];
    for (int i = 1; i < 7; ++i) {
      fout << " " << freq[i];
    }
    fout << endl;
    return 0;
}
