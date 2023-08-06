#include <string>
#include <vector>

#include "result_check/result_check.h"

class Solution {
public:
  int CharacterReplacement(const std::string &s, int k) {
    std::vector<int> hist('Z' - 'A' + 1);
    int l = 0;
    int u = 0;
    int max_cnt = 0;
    char max_c = s[0];
    int max_length = 0;
    while (u < s.size()) {
      if (u - l - max_cnt <= k) {
        if (max_cnt < ++hist[s[u] - 'A']) {
          max_cnt = hist[s[u] - 'A'];
          max_c = s[u];
        }
        ++u;
      }
      if (u - l - max_cnt > k) {
        --hist[s[l] - 'A'];
        if (s[l] == max_c) {
          --max_cnt;
        }
        for (int i = 0; i < hist.size(); ++i) {
          if (max_cnt < hist[i]) {
            max_cnt = hist[i];
            max_c = i - 'A';
          }
        }
        ++l;
      }
      if (max_length < u - l) {
        max_length = u - l;
      }
    }
    return max_length;
  }
};

int main() {
  const std::vector<std::pair<std::string, int>> cases = {
      std::make_pair("ABAB", 2),
      std::make_pair("AABABBA", 1),
  };

  const std::vector<int> expects = {
      4,
      4,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    int result = solution.CharacterReplacement(cs.first, cs.second);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}