#include <string>
#include <tuple>
#include <vector>

#include "result_check/result_check.h"

class Solution {
private:
  using IdxElement = std::tuple<int, int, char, int>;
  using IdxVector = std::vector<IdxElement>;

  IdxVector ProcessSub(IdxVector::iterator b, IdxVector::iterator e) {
    IdxVector result;
    IdxVector::iterator b1 = b, e1 = b;
    while (e1 != e && std::get<2>(*e1) == 'R')
      ++e1;
    b1 = e1 - 1;
    while (b1 >= b && e1 < e) {
      if (std::get<1>(*b1) == std::get<1>(*e1)) {
        --b1;
        ++e1;
      } else if (std::get<1>(*b1) < std::get<1>(*e1)) {
        --b1;
        --std::get<1>(*e1);
      } else if (std::get<1>(*b1) > std::get<1>(*e1)) {
        --std::get<1>(*b1);
        ++e1;
      }
    }
    result.insert(result.end(), b, b1 + 1);
    result.insert(result.end(), e1, e);

    return result;
  }

public:
  std::vector<int> SurvivedRobotsHealths(const std::vector<int> &positions,
                                         const std::vector<int> &healths,
                                         const std::string directions) {
    IdxVector pos_idx;
    for (int i = 0; i < positions.size(); ++i) {
      pos_idx.emplace_back(positions[i], healths[i], directions[i], i);
    }
    std::sort(pos_idx.begin(), pos_idx.end());

    IdxVector full_result;
    for (bool finished = false; !finished;) {
      full_result.clear();
      finished = true;
      IdxVector::iterator b = pos_idx.begin(), e = pos_idx.begin();
      for (; e != pos_idx.end();) {
        while (e != pos_idx.end() && std::get<2>(*e) == 'R') {
          ++e;
        }
        while (e != pos_idx.end() && std::get<2>(*e) == 'L') {
          ++e;
        }
        IdxVector processed = ProcessSub(b, e);
        if (processed.size() < e - b) {
          finished = false;
        }
        std::move(processed.begin(), processed.end(),
                  std::back_inserter(full_result));
        b = e;
      }
      if (!finished) {
        pos_idx.clear();
        std::move(full_result.begin(), full_result.end(),
                  std::back_inserter(pos_idx));
      }
    }
    std::sort(full_result.begin(), full_result.end(),
              [](IdxElement &l, IdxElement &r) {
                return std::get<3>(l) < std::get<3>(r);
              });

    std::vector<int> result;
    std::transform(full_result.begin(), full_result.end(),
                   std::back_inserter(result),
                   [](IdxElement &el) { return std::get<1>(el); });

    return result;
  }
};

int main() {
  const std::vector<std::tuple<std::vector<int>, std::vector<int>, std::string>>
      cases = {
          std::make_tuple(std::vector<int>({5, 4, 3, 2, 1}),
                          std::vector<int>({2, 17, 9, 15, 10}), "RRRRR"),
          std::make_tuple(std::vector<int>({3, 5, 2, 6}),
                          std::vector<int>({10, 10, 15, 12}), "RLRL"),
          std::make_tuple(std::vector<int>({1, 2, 5, 6}),
                          std::vector<int>({10, 10, 11, 11}), "RLRL"),
          std::make_tuple(
              std::vector<int>({1, 3, 5, 6, 8, 11, 14, 16, 24}),
              std::vector<int>({76, 23, 15, 34, 65, 77, 43, 13, 89}),
              "LRRLLRLLL"),
      };
  const std::vector<std::vector<int>> expects = {
      {2, 17, 9, 15, 10},
      {14},
      {},
      {76, 32, 65, 88},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<int> result = solution.SurvivedRobotsHealths(
        std::get<0>(cs), std::get<1>(cs), std::get<2>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}