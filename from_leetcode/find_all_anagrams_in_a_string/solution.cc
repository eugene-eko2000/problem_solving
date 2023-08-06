#include <string>
#include <vector>

#include "result_check/result_check.h"

class Solution {
public:
  std::vector<int> FindAnagrams(std::string s, std::string p) {
    if (p.size() > s.size()) {
      return {};
    }
    std::vector<int> counts('z' - 'a' + 1);
    for (char c : p) {
      ++counts[c - 'a'];
    }
    int unique_cnt = 0;
    for (int cnt : counts) {
      if (cnt > 0) {
        ++unique_cnt;
      }
    }
    // First histogram count
    std::vector<int> local_counts('z' - 'a' + 1);
    int a_count = 0;
    int c_begin = 0;
    int c_end = 0;
    std::vector<int> result;
    for (;;) {
      if (a_count == unique_cnt)
        result.push_back(c_begin);
      if (c_end >= s.size()) {
        break;
      }
      if (c_end - c_begin == p.size()) {
        if (local_counts[s[c_begin] - 'a'] == counts[s[c_begin] - 'a']) {
          --a_count;
        }
        --local_counts[s[c_begin] - 'a'];
        ++c_begin;
      }
      ++local_counts[s[c_end] - 'a'];
      if (local_counts[s[c_end] - 'a'] == counts[s[c_end] - 'a']) {
        ++a_count;
      }
      ++c_end;
    }
    return result;
  }
};

int main(int, char **) {
  const std::vector<std::pair<std::string, std::string>> cases = {
      std::make_pair("cbaebabacd", "abc"),
      std::make_pair("abab", "ab"),
  };

  const std::vector<std::vector<int>> expects = {
      {0, 6},
      {0, 1, 2},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<int> result = solution.FindAnagrams(cs.first, cs.second);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}