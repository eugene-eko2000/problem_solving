#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "result_check/result_check.h"

class Solution {
public:
  int MaxStarSum(const std::vector<int> &vals,
                 const std::vector<std::vector<int>> &edges, int k) {
    auto val_comp = [&vals](int v1, int v2) { return vals[v1] > vals[v2]; };

    std::vector<std::vector<int>> graph(vals.size());
    for (auto &edge : edges) {
      graph[edge[0]].push_back(edge[1]);
      graph[edge[1]].push_back(edge[0]);
    }
    int max_star_sum = vals[0];
    for (int curr_vertex = 0; curr_vertex < vals.size(); ++curr_vertex) {
      std::sort(graph[curr_vertex].begin(), graph[curr_vertex].end(), val_comp);
      int peer_cnt = 0;
      int star_sum = vals[curr_vertex];
      for (auto peer : graph[curr_vertex]) {
        if (peer_cnt >= k || vals[peer] < 0) {
          break;
        }
        star_sum += vals[peer];
        ++peer_cnt;
      }
      if (max_star_sum < star_sum) {
        max_star_sum = star_sum;
      }
    }
    return max_star_sum;
  }
};

int main(int, char **) {
  const std::vector<
      std::tuple<std::vector<int>, std::vector<std::vector<int>>, int>>
      cases = {
          std::make_tuple(std::vector<int>({1, 2, 3, 4, 10, -10, -20}),
                          std::vector<std::vector<int>>(
                              {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}}),
                          2),
          std::make_tuple(std::vector<int>({-5}),
                          std::vector<std::vector<int>>({}), 0),
      };

  const std::vector<int> expects = {
      16,
      -5,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    int result =
        solution.MaxStarSum(std::get<0>(cs), std::get<1>(cs), std::get<2>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}