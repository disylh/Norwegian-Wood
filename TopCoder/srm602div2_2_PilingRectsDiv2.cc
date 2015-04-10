#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;
using std::ceil;
using std::min;
using std::max;

class PilingRectsDiv2 {
public:
  int getmax(vector <int> X, vector <int> Y, int limit) {
    int ret = 0;
    bool exit = false;
    for (int i = 1, j = 0, curr = 0, n = X.size(); i <= 200 && !exit; ++i) {
        if (i * i >= limit) {
          j = i;
          exit = true;
        } else {
			j = static_cast<int>(ceil(limit * 1.0 / i));
		}
		curr = 0;
		for (int t = 0; t < n; ++t) {
		  if (i <= min(X[t], Y[t]) && j <= max(X[t], Y[t])) {
		    ++curr;
		  }
		}
		ret = max(curr, ret);
    }
    return ret == 0 ? -1 : ret;
  }
};
