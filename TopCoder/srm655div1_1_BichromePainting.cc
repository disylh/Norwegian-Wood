#include <string>
#include <vector>
#include <initializer_list>
#include <cassert>
#include <iostream>

using namespace std;

class BichromePainting {
  public:
    string isThatPossible(vector<string> board, int k) {
     int n = board.size();
     while (true) {
       bool change = false;
       for (int i = 0; i + k <= n; ++i) {
         for (int j = 0; j + k <= n; ++j) {
           int c = 0;
           for (int ii = i; ii < i + k && c != 3; ++ii) {
             for (int jj = j; jj < j + k; ++jj) {
               if (board[ii][jj] == 'B') {
                 c |= 1;
               } else if (board[ii][jj] == 'W') {
                 c |= 2;
               }
               if (c == 3) {
                 break;
               }       
             }
           }
           if (c == 1 || c == 2) {
             for (int ii = i; ii < i + k; ++ii) {
               for (int jj = j; jj < j + k; ++jj) {
                 board[ii][jj] = '*';
               }
             }
             change = true;
           }
         }
       }
       if (!change) {
         break;
       }
     }
     for (int i = 0; i < n; ++i) {
       for (int j = 0; j < n; ++j) {
         if (board[i][j] != '*') {
           return "Impossible";
         }
       }
     }
     return "Possible";
   }

   string isThatPossible2(vector<string> board, int k) {
     int n = board.size();
     for (int i = 0; i < n; ++i) {
       cout << board[i] << endl;
     }
     vector<vector<pair<int, int> > > m(n, vector<pair<int, int> >(n, {1, 1}));
     for (int i = 0; i < n; ++i) {
       for (int j = n - 2; j >= 0; --j) {
         if (board[i][j] == board[i][j + 1]) {
           m[i][j].first = m[i][j + 1].first + 1;
         }
       }
     }
     for (int j = 0; j < n; ++j) {
       for (int i = n - 2; i >= 0; --i) {
         if (board[i][j] == board[i + 1][j]) {
           m[i][j].second = m[i + 1][j].second + 1;
         }
       }
     }
     for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << m[i][j].second << " ";
      }
      cout << endl;
     }
     for (int i = 0; i < n; ++i) {
       for (int j = 0, h = 0, l = 0; j < n;) {
         if (m[i][j].first < k) {
           j += m[i][j].first;
           continue;
         }
         l = j, h = INT_MAX;
         while (l < j + m[i][j].first && m[i][l].second >= k &&
                board[i][l] == board[i][j]) {
           h = min(h, m[i][l].second);
           ++l;
         }
         if (l - j < k) {
           j += max(l - j, 1);
           continue;
         }
         cout << "i: " << i << " j: " << j << " h: " << h << " l: " << l << endl;
         bool pass = true, goon1 = false, goon2 = false;
         for (int t = 1;
              i - t >= 0 || i + h - 1 + t < n || j - t >= 0 || l + t - 1 < n; ++t) {
           if (i - t >= 0 || i + h - 1 + t < n) {
             goon1 = i - t < 0;
             goon2 = i + h - 1 + t >= n;
             for (int s = max(0, j - t), e = min(n - 1, l + t - k);
                  s <= e && (!goon1 || !goon2); ++s) {
               if (i - t >= 0 && m[i - t][s].first >= k) {
                 goon1 = true;
               }
               if (i + h - 1 + t < n && m[i + h - 1 + t][s].first >= k) {
                 goon2 = true;
               }
             }
             cout << "ti: " << t << " goon1: " << goon1 << " goon2: " << goon2 << endl;
             if (!goon1 || !goon2) {
               pass = false;
               break;
             }
           }
           if (pass && (j - t >= 0 || l + t - 1 < n)) {
             goon1 = j - t < 0;
             goon2 = l + t - 1 >= n;
             for (int s = max(0, i - t), e = min(n - 1, i + h + t - k);
                  s <= e && (!goon1 || !goon2); ++s) {
               if (j - t >= 0 && m[s][j - t].second >= k) {
                 goon1 = true;
               }
               if (l + t - 1 < n && m[s][l + t - 1].second >= k) {
                 goon2 = true;
               }
             }
             cout << "tj: " << t << " goon1: " << goon1 << " goon2: " << goon2 << endl;
             if (!goon1 || !goon2) {
               pass = false;
               break;
             }
           }
           if (!pass) {
             break;
           }
         }
         if (pass) {
           return "Possible";
         }
         j += max(l - j, 1);
       }
     }
     return "Impossible";
   }
};

int main() {
  BichromePainting bp;
  cout << "test#1" << endl;
  assert(bp.isThatPossible({"BBBW", "BWWW", "BWWW", "WWWW"}, 3) == "Possible");
  cout << "test#2" << endl;
  assert(bp.isThatPossible({"BW", "WB"}, 2) == "Impossible");
  cout << "test#3" << endl;
  assert(bp.isThatPossible({"BWBWBB", "WBWBBB", "BWBWBB", "WBWBBB", "BBBBBB", "BBBBBB"}, 2) == "Possible");
  cout << "test#4" << endl;
  assert(bp.isThatPossible({"BWBWBB", "WBWBWB", "BWBWBB", "WBWBWB", "BWBWBB", "BBBBBB"}, 2) == "Impossible");
  cout << "test#5" << endl;
  assert(bp.isThatPossible({"BWBWBB", "WBWBWB", "BWBWBB", "WBWBWB", "BWBWBB", "BBBBBB"}, 1) == "Possible");
  cout << "test#6" << endl;
  assert(bp.isThatPossible({"BB", "BB"}, 1) == "Possible");
  cout << "test#7" << endl;
  assert(bp.isThatPossible({"BWWWWWB", "BWWWBBB", "WWBBBWW", "WWWWWBB", "WBWBWBW", "BWBBBWW", "BWWBBBW"}, 2) == "Impossible");
  cout << "test#8" << endl;
  assert(bp.isThatPossible({"BBBBBBWBBBBBB", "BBBBBBBWWWWWB", "BBBBBBBWWWWWB", "WWWBBBBWWWWWB", "WWBBBBBWWWWWB", "WBBBBBWWWWBBB", "WBBBBBWBBBBBB", "BBBBBBWBBBBBB", "WBBBBWWWBBBBB", "BBBWWWBBBBBBB", "BBBBWWBBBBBBW", "BBBBWWBBBBWWB", "BBBBWWBBBBWWB"}, 4) == "Possible");
  cout << "test#9" << endl;
  assert(bp.isThatPossible({"WWWWWWWWWWWWWWWW", "WWWWWWWWWWWWWWWW", "WWWWWWWWWWWWWWWB", "WWBBBWWWWWWWWWWB", "WWBBBWWWWWWWBWWB", "WWBBBWWWWWWWBWWW", "WWBBBWWWWWWWBWWW", "WWBBBBBBBBBBBWWW", "WWBBBBBBBBBBBWWW", "WWWBWWWWWWBBBWWW", "WWBBWWWWWWBBWWWW", "WWBBWWWWWWBBWWWW", "WWBBWWWWWWBBWWWW", "WWBBWWWWWWWWWWBW", "WWBBWWWWWWWWWWBW", "WWWWWWWWWWWWWWWW"}, 6) == "Possible");
  cout << "Success" << endl;
}

