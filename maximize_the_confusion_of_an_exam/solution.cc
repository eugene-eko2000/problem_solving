#include <queue>
#include <unordered_map>
#include <vector>

#include "result_check/result_check.h"

class Solution {
public:
  int MaxConsecutiveAnswers(const std::string& answerKey, int k) {
    int max_eq = 0;
    const std::vector<char> tf = {'T', 'F'};
    for (auto b_c : tf) {
      int l = 0;
      int u = 0;
      int k_cnt = k;
      for (; u < answerKey.size();) {
        if (k_cnt >= 0) {
          if (answerKey[u] == b_c) {
            --k_cnt;
          }
          ++u;
        }
        if (k_cnt < 0) {
          if (answerKey[l] == b_c) {
            ++k_cnt;
          }
          ++l;
        }
        if (max_eq < u - l) {
          max_eq = u - l;
        }
      }
    }

    return max_eq;
  }
};
int main(int, char **) {
  const std::vector<std::pair<std::string, int>> cases = {
      std::make_pair("TTFF", 2),
      std::make_pair("TFFT", 1),
      std::make_pair("TTFTTFTT", 1),
  };

  const std::vector<int> expects = {
      4,
      3,
      5,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    int result = solution.MaxConsecutiveAnswers(cs.first, cs.second);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}