#include <vector>

class TypoCoderDiv2 {
 public:
  int count(std::vector<int> rating) {
    bool flag = true;
    int ret = 0;
    for (auto &i : rating) {
      if (flag && i >= 1200) {
        flag = false;
        ++ret;
      } else if (!flag && i < 1200) {
        flag = true;
        ++ret;
      }
    }
    return ret;
  }
};
