#include <queue>
#include <unordered_map>
#include <vector>

#include "result_check/result_check.h"

class Solution {
public:
  std::vector<int> TopKFrequent(const std::vector<int> &nums, int k) const {
    std::unordered_map<int, int> hist;
    for (int n : nums) {
      ++hist[n];
    }
    std::priority_queue<std::pair<int, int>> most_freq;
    for (auto &el : hist) {
      most_freq.emplace(el.second, el.first);
    }
    std::vector<int> result;
    for (int i = 0; i < k; ++i) {
      result.push_back(most_freq.top().second);
      most_freq.pop();
    }
    return result;
  }
};

int main() {
  const std::vector<std::pair<std::vector<int>, int>> cases = {
      std::make_pair(std::vector<int>({1, 1, 1, 2, 2, 3}), 2),
      std::make_pair(std::vector<int>({1}), 1),
  };

  const std::vector<std::vector<int>> expects = {
      {1, 2},
      {1},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<int> result = solution.TopKFrequent(cs.first, cs.second);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}