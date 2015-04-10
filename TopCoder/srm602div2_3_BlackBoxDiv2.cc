#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class BlackBoxDiv2 {
 public:
  int count(string front, string side) {
    int m = count_b(front), n = count_b(side);
    if (m == 0 && n == 0) {
      return 1;
    } else if (m * n == 0) {
      return 0;
    } else {
      return calc(m, n);
    }
  }

 private:
  int count_b(const string &str) {
    int ret = 0;
    for (auto &c : str) {
      if (c == 'B') {
        ++ret;
      }
    }
    return ret;
  }
  unsigned long long mod_pow(unsigned long long x, unsigned long long n,
                             unsigned long long p) {
    unsigned long long ret = x == 0 ? 0 : 1;
    while (x != 0 && n) {
      if (n % 2) {
        ret = ret * x % p;
      }
      x = x * x % p;
      n /= 2;
    }
    return ret;
  }
  unsigned long long mod_inverse(unsigned long long x, unsigned long long p) {
    return mod_pow(x, p - 2, p);
  }
  unsigned long long c(int x, int y, const vector<unsigned long long> &fv) {
    return fv[x] * mod_inverse(fv[x - y] * fv[y] % MOD, MOD) % MOD;
  }
  int calc(int m, int n) {
    if (m > n) {
      return calc(n, m);
    }
    vector<vector<unsigned long long> > dp(
        m + 1, vector<unsigned long long>(n + 1, 1));
    vector<unsigned long long> fv(MN + 1, 1);
    for (int i = 1; i <= MN; ++i) {
      fv[i] = fv[i - 1] * i % MOD;
    }
    unsigned long long temp = 0;
    for (int i = 2; i <= m; ++i) {
      for (int j = 2; j <= n; ++j) {
        dp[i][j] = 0;
        for (int k = 0; k < i; ++k) {
          temp = (c(i, k, fv) * ((1LL << (i - k)) % MOD)) % MOD;
          temp = temp * dp[i - k][j - 1] % MOD;
          dp[i][j] = (dp[i][j] + temp) % MOD;
        }
        dp[i][j] = (dp[i][j] - dp[i][j - 1] + MOD) % MOD;
      }
    }
    return dp[m][n];
  }
  const unsigned long long MOD = 1000000007;
  const int MN = 50;
};
