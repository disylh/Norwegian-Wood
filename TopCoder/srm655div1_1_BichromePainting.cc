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

