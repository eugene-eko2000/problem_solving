#include <algorithm>
#include <tuple>
#include <vector>

#include "result_check/result_check.h"

class Solution {
private:
  std::vector<int> FindMiddle(const std::vector<int> &nums1,
                              const std::vector<int> &nums2) {
    std::vector<int>::const_iterator i = nums1.begin();
    std::vector<int>::const_iterator j = nums2.begin();
    int pos = -1;
    int curr;
    if (i == nums1.end()) {
      curr = *j;
    } else if (j == nums2.end()) {
      curr = *i;
    } else {
      curr = std::min(*i, *j);
    }
    int half = (nums1.size() + nums2.size()) / 2;
    int prev = curr;
    for (; pos < half;) {
      prev = curr;
      if (i == nums1.end()) {
        curr = *j;
        ++j;
      } else if (j == nums2.end()) {
        curr = *i;
        ++i;
      } else if (*i < *j) {
        curr = *i;
        ++i;
      } else {
        curr = *j;
        ++j;
      }
      ++pos;
    }
    if ((nums1.size() + nums2.size()) % 2 == 0) {
      return {prev, curr};
    }
    return {curr};
  }

public:
  double FindMedianSortedArrays(const std::vector<int> &nums1,
                                const std::vector<int> &nums2) {
    std::vector<int> middle = FindMiddle(nums1, nums2);
    if (middle.size() % 2 == 0) {
      return (double(middle[0]) + double(middle[1])) / 2;
    }
    return middle[0];
  }
};

int main() {
  const std::vector<std::tuple<std::vector<int>, std::vector<int>>> cases = {
      std::make_tuple(std::vector<int>({1, 3}), std::vector<int>({2})),
      std::make_tuple(std::vector<int>({1, 2}), std::vector<int>({3, 4})),
  };

  const std::vector<double> expects = {
      2.0,
      2.5,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    double result =
        solution.FindMedianSortedArrays(std::get<0>(cs), std::get<1>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}