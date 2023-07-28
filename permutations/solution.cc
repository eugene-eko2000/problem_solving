#include <vector>

#include "result_check/result_check.h"

class Solution {
private:
  std::vector<std::vector<int>>
  PermuteRecursive(std::vector<int>::const_iterator start,
                   std::vector<int>::const_iterator end) {
    if (start == end) {
      return std::vector<std::vector<int>>();
    }
    int head_num = *start;
    std::vector<std::vector<int>> tail_permutations =
        PermuteRecursive(start + 1, end);
    std::vector<std::vector<int>> result;
    if (tail_permutations.empty()) {
      result.emplace_back();
      result.back().push_back(head_num);
      return result;
    }
    for (int i = 0; i <= tail_permutations[0].size(); ++i) {
      for (const std::vector<int> &p : tail_permutations) {
        result.emplace_back(p.begin(), p.begin() + i);
        result.back().push_back(head_num);
        if (p.begin() + i < p.end()) {
          result.back().insert(result.back().end(), p.begin() + i, p.end());
        }
      }
    }
    return result;
  }

public:
  std::vector<std::vector<int>> Permute(const std::vector<int> &nums) {
    std::vector<std::vector<int>> result =
        PermuteRecursive(nums.begin(), nums.end());
    return result;
  }
};

int main(int, char **) {
  const std::vector<std::vector<int>> cases = {
      {1, 2, 3},
      {0, 1},
      {1},
  };

  const std::vector<std::vector<std::vector<int>>> expects = {
      {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {3, 1, 2}, {2, 3, 1}, {3, 2, 1}},
      {{0, 1}, {1, 0}},
      {{1}},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<std::vector<int>> result = solution.Permute(cs);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}