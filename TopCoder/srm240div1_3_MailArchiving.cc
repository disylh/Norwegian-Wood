#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MailArchiving {
 public:
  int minSelections(vector<string> destFolders) {
    int n = destFolders.size();
    unsigned int dp[n][n];
    memset(dp, -1, sizeof(dp[0][0]) * n * n);
    for (int i = 0; i < n; ++i) {
      dp[i][i] = 1;
    }
    for (int l = 1; l < n; ++l) {
      for (int i = 0; i < n - l; ++i) {
        for (int k = i; k < i + l; ++k) {
          dp[i][i + l] =
              min(dp[i][i + l],
                  dp[i][k] + dp[k + 1][i + l] -
                      (destFolders[k] == destFolders[k + 1] ? 1 : 0) -
                      (destFolders[i] == destFolders[i + l] ? 1 : 0) +
                      (destFolders[i] == destFolders[k] &&
                               destFolders[k] == destFolders[k + 1] &&
                               destFolders[k + 1] == destFolders[i + l]
                           ? 1
                           : 0));
        }
      }
    }
    return dp[0][n - 1];
  }
};
